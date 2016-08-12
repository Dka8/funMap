#include "Layer.h"
#include "Drawable.h"
#include "ItemManager.h"
#include "Window.h"
#include <SFML\Graphics.hpp>

namespace wv {

	Layer::Layer(wv::SharedContext* l_context, const nlohmann::json& l_json)
		: m_context(l_context) {
		loadFromJson(l_json);
	}
	Layer::~Layer() {};

	void Layer::loadFromJson(const nlohmann::json& l_json) {
		std::string layerType = l_json["content"].get<std::string>();
		std::string texture = l_json["texture"].get<std::string>();
		stringToLayerType(layerType);
		
		nlohmann::json types = l_json["types"];
		for (auto &type : types) {
			type["texture"] = texture;
			type["content"] = layerType;
			addItem(type);
		}

		nlohmann::json tiles = l_json["tiles"];
		for (auto &tile : tiles) {
			addObject(tile);
		}
	}

	void Layer::addItem(const nlohmann::json& l_json) {
		wv::DrawableType drawableType;
		if (l_json["content"].get<std::string>() == "tiles") {
			drawableType = wv::DrawableType::Tile;
		}
		else {
			drawableType = wv::DrawableType::Sprite;
		}
		m_context->m_itemManager->addDrawable(drawableType, l_json);
	}
	void Layer::addObject(const nlohmann::json& l_json, bool l_isSort) {
		std::string objectName = l_json["type"].get<std::string>();
		sf::Vector2i objectPos = sf::Vector2i(l_json["x"].get<int>(),
												l_json["y"].get<int>());
		wv::Drawable* drawable = m_context->m_itemManager->getDrawable(objectName);
		Object* object = new Object(std::make_pair(drawable, objectPos));
		m_objects.push_back(object);
		if (l_isSort) {
			//sort();
		}
	}

	void Layer::draw() {
		sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
		sf::View windowView = window->getView();
		//sf::Vector2i windowViewCenter = wv::Drawable::mapPixelToCoords(windowView.getCenter());
		//sf::Vector2i windowViewSize = wv::Drawable::mapPixelToCoords(windowView.getSize());


		sf::FloatRect viewRect = sf::FloatRect(windowView.getCenter().x - windowView.getSize().x / 2.f,
											windowView.getCenter().y - windowView.getSize().y / 2.f,
											windowView.getSize().x, windowView.getSize().y);
		
		for (auto &object : m_objects) {
			//std::string objectName = object->first;
			//wv::Drawable* drawable = m_context->m_itemManager->getDrawable(objectName);
			
			sf::Vector2i objectCoord = object->second;
			sf::Vector2f objectPos = wv::Drawable::mapCoordsToPixel(objectCoord);
			
			if ((objectPos.x > (viewRect.left - wv::Drawable::getScale())
				&& objectPos.x < (viewRect.left + viewRect.width + wv::Drawable::getScale()))
				&& (objectPos.y > (viewRect.top - wv::Drawable::getScale())
				&& objectPos.y < (viewRect.top + viewRect.height + wv::Drawable::getScale()))) {
				object->first->setCoords(objectCoord);
				window->draw(*object->first);
			}
		}
	}

	void Layer::stringToLayerType(const std::string& l_type) {
		if (l_type == "background")
			m_type = LayerType::BackGround;
		else if (l_type == "tiles")
			m_type = LayerType::Ground;
	}

	LayerType Layer::getLayerType() { return m_type; }
}