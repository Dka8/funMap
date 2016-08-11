#ifndef WV_SHAREDCONTEXT_H
#define WV_SHAREDCONTEXT_H
#include "ResourceManager.hpp"
#include "EventManager.h"

namespace wv {
	class Window;
	class MapViewer;

	struct SharedContext {
		SharedContext():
		m_window			(nullptr),
		m_mapViewer			(nullptr),
		m_textureManager	(nullptr),
		m_itemManager		(nullptr)
		{}

		wv::Window*			m_window;
		wv::MapViewer*		m_mapViewer;
		utils::ResourceManager<sf::Texture, std::string>* m_textureManager;
		wv::ItemManager*	m_itemManager;
	};
}

#endif // !WV_SHAREDCONTEXT_H