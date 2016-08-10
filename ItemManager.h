#ifndef MAP_TILE_H
#define MAP_TILE_H
#include <SFML\Graphics.hpp>
#include "Drawable.h"
#include "ResourceManager.hpp"
#include "json.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>

namespace wv {
	
	using Items = std::unordered_map<std::string, wv::Drawable*>;

	enum class DrawableType	{
		Tile, Sprite
	};
	
	using DrawableFactoy = std::unordered_map<DrawableType, std::function<wv::Drawable*(void)>>;

	class ItemManager {
	public:
		wv::Drawable* operator[] (const std::string& l_key) {
			wv::Drawable* drawable = getDrawable(l_key);
			return drawable;
		}
		ItemManager(const ItemManager&) = delete;
		ItemManager& operator = (const ItemManager&) = delete;

		ItemManager(ItemManager&&) = default;
		ItemManager& operator = (ItemManager&&) = default;

		ItemManager(utils::ResourceManager<sf::Texture, std::string>* l_textMgr)
			: m_textureMgr(l_textMgr) {
			m_factory[DrawableType::Tile] = [this](){return new wv::Tile; };
			m_factory[DrawableType::Sprite] = [this]() {return new wv::Sprite; };
		};
		
		~ItemManager() {};

		void setTextureMgr(utils::ResourceManager<sf::Texture, std::string>* l_mgr) {
			m_textureMgr = l_mgr;
		}

		bool addDrawable(const DrawableType& l_type, 
			const nlohmann::json& l_json) {
			auto itr = m_factory.find(l_type);
			if (itr == m_factory.end()) {
				std::cout << "DrawableType not found. add Drawable fail\n";
				return false;
			}
			auto newDrawable = itr->second();
			std::string drawableName = "";
			try {
				drawableName = l_json["name"].get<std::string>();
			} catch(...){}
			if (drawableName == "") { return false; }
			try	{
				std::string textureName = l_json["texture"].get<std::string>();
				newDrawable->setTexture(m_textureMgr->getOrLoad(drawableName, textureName));
				newDrawable->setTexture(&(m_textureMgr->getOrLoad(drawableName, textureName)));
			} catch(...){}
			try {
				nlohmann::json rect = l_json["rect"];
				newDrawable->setTextureRect(sf::IntRect::Rect(rect["x"].get<int>(),
																rect["y"].get<int>(),
																rect["width"].get<int>(),
																rect["height"].get<int>()));
			} catch(...){}
			
			m_entries.emplace(drawableName, newDrawable);
			return true;
		}
				
		wv::Drawable* getDrawable(const std::string l_name) {
			auto itr = m_entries.find(l_name);
			if (itr == m_entries.end()) {
				std::cout << "Drawable not found. getDrawable fail\n";
				return nullptr;
			}
			return itr->second;
		}
	
	private:
		Items			m_entries;
		DrawableFactoy	m_factory;
		utils::ResourceManager<sf::Texture, std::string>* m_textureMgr;
	};
}

#endif // !MAP_TILE_H