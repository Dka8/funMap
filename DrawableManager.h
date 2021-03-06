#ifndef MAP_TILE_H
#define MAP_TILE_H
#include <SFML\Graphics.hpp>
#include "Drawable.h"
#include "ResourceManager.hpp"
#include "json.hpp"
#include <iostream>
#include <unordered_map>
#include <fstream>

namespace wv {
	
	using Drawables = std::unordered_map<std::string, wv::Drawable*>;

	//using DrawableFactoy = std::unordered_map<DrawableType, std::function<wv::Object*(void)>>;

	class DrawableManager {
	public:
		wv::Drawable* operator[] (const std::string& l_key) {
			wv::Drawable* drawable = getDrawable(l_key);
			return drawable;
		}
		DrawableManager(const DrawableManager&) = delete;
		DrawableManager& operator = (const DrawableManager&) = delete;

		DrawableManager(DrawableManager&&) = default;
		DrawableManager& operator = (DrawableManager&&) = default;

		DrawableManager(utils::ResourceManager<sf::Texture, std::string>* l_textMgr)
			: m_textureMgr(l_textMgr) {
			loadFromFile("drawables.json");
		};
		
		~DrawableManager() {};

		void loadFromFile(std::string l_file) {
			std::ifstream fin;
			fin.open(l_file);
			if (!fin.is_open()) {
				std::cout << "cannont open file with objects " << l_file << std::endl;
				return;
			}
			nlohmann::json data = nlohmann::json::parse(fin);
			fin.close();

			nlohmann::json objects = data["objects"];
			for (auto &object : objects) {
				if (!addDrawable(object)) {
					std::cout << "cannot add object " << object["name"].get<std::string>();
					return;
				}
			}
		}

		void setTextureMgr(utils::ResourceManager<sf::Texture, std::string>* l_mgr) {
			m_textureMgr = l_mgr;
		}

		bool addDrawable(const nlohmann::json& l_json) {
			Drawable* newObject = new Drawable(l_json, m_textureMgr);
			std::string objectName = "";
			try	{
				objectName = l_json["name"].get<std::string>();
			}
			catch(...){}
			if (objectName == "") { return false; }
			m_objects.emplace(objectName, newObject);
			std::cout << "added drawable " << objectName << std::endl;
			return true;
		}
				
		wv::Drawable* getDrawable(const std::string l_name) {
			auto itr = m_objects.find(l_name);
			if (itr == m_objects.end()) {
				std::cout << "Drawable not found. getDrawable fail\n";
				return nullptr;
			}
			return itr->second;
		}
	
		bool getDrawableType(const wv::Drawable* l_drawable, std::string l_drName) {
			std::string type = "noname";
			for (auto& object : m_objects) {
				if (object.second == l_drawable) {
					l_drName = object.first;
					return true;
				}
			}
			return false;
		}

	private:
		Drawables			m_objects;
		utils::ResourceManager<sf::Texture, std::string>* m_textureMgr;
	};

	
}

#endif // !MAP_TILE_H