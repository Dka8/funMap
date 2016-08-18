#include "Map.h"
#include "Drawable.h"
#include "DrawableManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

namespace wv {

	Map::Map(wv::SharedContext* l_context, const std::string& l_file)
		: m_context(l_context) {
		loadFromFile(l_file);
	}

	Map::~Map() {};

	void Map::loadFromFile(const std::string& l_file) {
		std::ifstream fin;
		fin.open(l_file);
		if (!fin.is_open()) {
			std::cout << "cannot open file " << l_file;
		}
		nlohmann::json data = nlohmann::json::parse(fin);
		fin.close();
		loadFromJson(data);
	}

	void Map::loadFromJson(const nlohmann::json& l_json) {
		nlohmann::json items = l_json["items"];
		for (auto &item : items) {
			addItem(item);
		}
		S_Renderer* render = m_context->m_systemManager->GetSystem<S_Renderer>(System::Renderer);
		render->sort();
	}

	void Map::addItem(const nlohmann::json& l_json) {
		std::string itemType = l_json["type"].get<std::string>();
		sf::Vector2i itemCoords = sf::Vector2i(l_json["x"].get<int>(),
												l_json["y"].get<int>());
		int entity = m_context->m_entityManager->AddEntity(itemType);
		C_Position* itemPosition = m_context->m_entityManager->GetComponent<C_Position>(entity, Component::Position);
		itemPosition->setPosition(itemCoords);

		//wv::Drawable* drawable = m_context->m_drawableManager->getDrawable(itemType);
		//if (drawable) {
		//	m_items.emplace(itemCoords, drawable);
		//}
	}
	wv::Drawable* Map::getItem(const sf::Vector2i& l_pos) {
		auto itr = m_items.find(l_pos);
		if (itr == m_items.end()) {
			return nullptr;
		}
		else return itr->second;
	}

	void Map::draw() {
		/*sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
		sf::View windowView = window->getView();

		sf::FloatRect viewRect = sf::FloatRect(windowView.getCenter().x - windowView.getSize().x / 2.f,
			windowView.getCenter().y - windowView.getSize().y / 2.f,
			windowView.getSize().x, windowView.getSize().y);

		for (auto &item : m_items) {
			
			sf::Vector2i itemCoord = item.first;
			sf::Vector2f itemPos = wv::Drawable::mapCoordsToPixel(itemCoord);

			if ((itemPos.x > (viewRect.left - wv::Drawable::getScale())
				&& itemPos.x < (viewRect.left + viewRect.width + wv::Drawable::getScale()))
				&& (itemPos.y > (viewRect.top - wv::Drawable::getScale())
					&& itemPos.y < (viewRect.top + viewRect.height + wv::Drawable::getScale()))) {
				item.second->setCoords(itemCoord);
				window->draw(*(item.second));
			}
		}*/
	}
	wv::Items* Map::getItems() { return &m_items; }
}