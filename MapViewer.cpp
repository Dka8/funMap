#include "MapViewer.h"
#include "Window.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

namespace wv {

	MapViewer::MapViewer(wv::SharedContext* l_context):
		m_context		(l_context),
		m_moveSpeed		(300),
		m_moveVector	(sf::Vector2i(0,0)),
		m_zoomFactor	(1),
		m_map			(nullptr)
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
		event->AddCallback("emplaceTree", &MapViewer::react, this);

		m_map = new wv::Map(m_context, "map.json");
		m_context->m_entityManager->AddEntity("empty");
	}
	MapViewer::~MapViewer(){}
	
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
	}

	void MapViewer::draw() {
		if (m_map) {
			m_map->draw();
		}
		
		//sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
		//sf::Vector2i mousePixels = sf::Mouse::getPosition(*m_context->m_window->GetRenderWindow());
		//sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);

		//sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
		//m_mouse.second->setCoords(mouseCoords);
		//window->draw(*m_mouse.second);
	}
	wv::Map* MapViewer::getMap() { return m_map; }

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
	}
}
