#include "MapViewer.h"
#include "Window.h"
#include "ItemManager.h"

namespace wv {

	MapViewer::MapViewer(wv::SharedContext* l_context):
		m_context		(l_context),
		m_moveSpeed		(200),
		m_moveVector	(sf::Vector2i(0,0))
	{
		wv::EventManager* event = m_context->m_window->GetEventManager();
		event->AddCallback("moveLeft", &MapViewer::react, this);
		event->AddCallback("moveRight", &MapViewer::react, this);
		event->AddCallback("moveUp", &MapViewer::react, this);
		event->AddCallback("moveDown", &MapViewer::react, this);

		nlohmann::json item;
		item["name"] = "water";
		item["texture"] = "tiles.jpg";
		item["rect"] = { { "x", 0 },{ "y", 0 },
		{ "width", 100 },{ "height", 100 } };

		m_context->m_itemManager->addDrawable(wv::DrawableType::Tile, item);
	}
	MapViewer::~MapViewer(){}

	void MapViewer::loadMapFromFile(const std::string l_file){}
	
	void MapViewer::update(sf::Time l_time) {
		//sf::View* view = m_window->GetWindowView();
		//std::cout << m_moveVector.x << " " << m_moveVector.y << std::endl;
		if (m_moveVector != sf::Vector2i(0, 0)) {
			sf::Vector2f offset = sf::Vector2f(m_moveVector.x * m_moveSpeed * l_time.asSeconds(),
				m_moveVector.y * m_moveSpeed * l_time.asSeconds());
			m_context->m_window->moveView(offset);
			m_moveVector = sf::Vector2i(0, 0);
		}
	}

	void MapViewer::draw() {
		auto drawable = m_context->m_itemManager->getDrawable("water");
		m_context->m_window->GetRenderWindow()->draw(*drawable);
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
	}
}
