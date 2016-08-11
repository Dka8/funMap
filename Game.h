#pragma once
#include "Window.h"
#include "EventManager.h"
#include <iostream>
#include "SharedContext.h"

namespace wv {

	class Game {
	public:
		Game();
		~Game();

		void Update();
		void Render();

		sf::Time GetElapsed();
		void RestartClock();

		Window* GetWindow();
		wv::SharedContext*	getSharedContext();
	private:
		Window m_window;
		sf::Clock Clock;
		sf::Time	m_deltaTime;
		
		wv::SharedContext	m_context;
	};
}