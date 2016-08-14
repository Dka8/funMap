#include "MapViewer.h"
#include "Window.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

namespace wv {

	MapViewer::MapViewer(wv::SharedContext* l_context):
		m_context		(l_context),
		m_moveSpeed		(200),
		m_moveVector	(sf::Vector2i(0,0)),
		m_zoomFactor	(1),
		m_map			(nullptr),
		m_mouse			(nullptr)
	{
		wv::EventManager* event = m_context->m_window->GetEventManager();
		event->AddCallback("moveLeft", &MapViewer::react, this);
		event->AddCallback("moveRight", &MapViewer::react, this);
		event->AddCallback("moveUp", &MapViewer::react, this);
		event->AddCallback("moveDown", &MapViewer::react, this);
		event->AddCallback("zoom", &MapViewer::react, this);
		event->AddCallback("tree1", &MapViewer::react, this);
		event->AddCallback("tree2", &MapViewer::react, this);
		event->AddCallback("tree3", &MapViewer::react, this);
		event->AddCallback("tree4", &MapViewer::react, this);
		event->AddCallback("tree5", &MapViewer::react, this);
		event->AddCallback("tree6", &MapViewer::react, this);
		event->AddCallback("empty", &MapViewer::react, this);

		loadMapFromFile("layer.json");
		m_mouse = m_context->m_itemManager->getDrawable("empty");
	}
	MapViewer::~MapViewer(){}

	void MapViewer::loadMapFromFile(const std::string l_file){
		std::ifstream fin;
		fin.open(l_file);
		if (!fin.is_open()) {
			std::cout << "cannot open file with map" << std::endl;
			return;
		}
		nlohmann::json map = nlohmann::json::parse(fin);
		fin.close();
		loadMapFromJson(map);
	}

	void MapViewer::loadMapFromJson(const nlohmann::json& l_json) {
		m_map = new wv::Map(m_context, l_json);
	}
	
	void MapViewer::update(sf::Time l_time) {
		//sf::View* view = m_window->GetWindowView();
		//std::cout << m_moveVector.x << " " << m_moveVector.y << std::endl;
		if (m_moveVector != sf::Vector2i(0, 0)) {
			sf::Vector2f offset = sf::Vector2f(m_moveVector.x * m_moveSpeed * l_time.asSeconds(),
				m_moveVector.y * m_moveSpeed * l_time.asSeconds());
			m_context->m_window->moveView(offset);
			m_moveVector = sf::Vector2i(0, 0);
		}
		if (m_zoomFactor != 1) {
			m_context->m_window->zoomView(m_zoomFactor);
			m_zoomFactor = 1;
		}
		sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
		sf::Vector2i mousePixels = sf::Mouse::getPosition(*m_context->m_window->GetRenderWindow());
		sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);

		sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
		m_mouse->setCoords(mouseCoords);
	}

	void MapViewer::draw() {
		if (m_map) {
			m_map->draw();
		}
		sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
		window->draw(*m_mouse);
	}

	void MapViewer::react(wv::EventDetails* l_details) {
		std::string event = l_details->m_name;
		if (event == "moveLeft") {
			m_moveVector = sf::Vector2i(-1, 0);
		}
		else if (event == "moveRight") {
			m_moveVector = sf::Vector2i(1, 0);
		}
		else if (event == "moveUp") {
			m_moveVector = sf::Vector2i(0, -1);
		}
		else if (event == "moveDown") {
			m_moveVector = sf::Vector2i(0, 1);
		}
		else if (event == "zoom") {
			m_zoomFactor = 1 - (l_details->m_mouseWheelDelta) / 20.f;
		}
		else if (event == "empty") {
			m_mouse = m_context->m_itemManager->getDrawable("empty");
		}
		else if (event == "tree1") {
			m_mouse = m_context->m_itemManager->getDrawable("tree1");
		}
		else if (event == "tree2") {
			m_mouse = m_context->m_itemManager->getDrawable("tree2");
		}
		else if (event == "tree3") {
			m_mouse = m_context->m_itemManager->getDrawable("tree3");
		}
		else if (event == "tree4") {
			m_mouse = m_context->m_itemManager->getDrawable("tree4");
		}
		else if (event == "tree5") {
			m_mouse = m_context->m_itemManager->getDrawable("tree5");
		}
		else if (event == "tree6") {
			m_mouse = m_context->m_itemManager->getDrawable("tree6");
		}
	}
}
