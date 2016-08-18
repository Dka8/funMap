#include "Game.h"
#include "MapViewer.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace wv {

	Game::Game() : m_window("Forest", sf::Vector2u(1600, 900), &m_context) {
		Clock.restart();
		
		m_context.m_window = &m_window;
		m_context.m_textureManager = new utils::ResourceManager<sf::Texture, std::string>;
		m_context.m_drawableManager = m_context.m_textureManager->makeItemManager();
		m_context.m_systemManager = new SystemManager(&m_context);
		m_context.m_entityManager = new EntityManager(&m_context);
		m_context.m_mapViewer = new wv::MapViewer(&m_context);
	}

	Game::~Game() {}

	sf::Time Game::GetElapsed() { return Clock.getElapsedTime(); }
	void Game::RestartClock() { m_deltaTime = Clock.restart(); }
	Window* Game::GetWindow() { return &m_window; }

	void Game::Update() {
		m_window.Update();
		m_context.m_mapViewer->update(m_deltaTime);
		m_context.m_systemManager->Update(m_deltaTime.asSeconds());
	}

	void Game::Render() {
		m_window.BeginDraw();
		// Render here.
		m_context.m_systemManager->Draw();
		m_context.m_mapViewer->draw();
		m_window.EndDraw();
	}

	wv::SharedContext* Game::getSharedContext() { return &m_context; }

}