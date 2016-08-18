#ifndef WV_SHAREDCONTEXT_H
#define WV_SHAREDCONTEXT_H
#include "ResourceManager.hpp"
#include "EventManager.h"
//#include "EntityManager.h"
//#include "SystemManager.h"

class EntityManager;
class SystemManager;

namespace wv {
	class Window;
	class MapViewer;

	struct SharedContext {
		SharedContext():
		m_window			(nullptr),
		m_mapViewer			(nullptr),
		m_textureManager	(nullptr),
		m_drawableManager	(nullptr),
		m_entityManager		(nullptr),
		m_systemManager		(nullptr)
		{}

		wv::Window*				m_window;
		wv::MapViewer*			m_mapViewer;
		utils::ResourceManager<sf::Texture, std::string>* m_textureManager;
		wv::DrawableManager*	m_drawableManager;
		EntityManager*			m_entityManager;
		SystemManager*			m_systemManager;
	};
}

#endif // !WV_SHAREDCONTEXT_H