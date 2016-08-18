#ifndef WV_MAPVIEWER_H
#define WV_MAPVIEWER_H
#include <iostream>
#include <string>
#include "json.hpp"
#include "SharedContext.h"
#include "Map.h"

namespace wv {

	class MapViewer
	{
	public:
		MapViewer() = delete;
		MapViewer(wv::SharedContext* l_context);
		~MapViewer();
		
		void update(sf::Time l_time);
		void draw();
	private:
		void react(wv::EventDetails* l_details);
		//void move(const sf::Vector2i& l_delta);
		//void zoom(const float l_zoom);
		//sf::Vector2i getMousePosition() const;


		float				m_zoomFactor;
		sf::Vector2i		m_moveVector;
		float				m_moveSpeed;
		wv::Map*			m_map;
		wv::SharedContext*	m_context;
		std::pair<std::string,wv::Drawable*>		m_mouse;
	};
}

#endif // !WV_MAPVIEWER_H