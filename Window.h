#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "SharedContext.h"

namespace wv {
	class MapViewer;
}

namespace wv {

	class Window {
	public:
		Window();
		Window(const std::string& title, const sf::Vector2u& size, wv::SharedContext* l_context);
		~Window();

		void BeginDraw();
		void EndDraw();

		void Update();

		bool IsDone() const;
		bool IsFullscreen() const;
		bool IsFocused() const;

		void ToggleFullscreen(EventDetails* l_details);
		void Close(EventDetails* l_details = nullptr);

		sf::RenderWindow* GetRenderWindow();
		EventManager* GetEventManager();
		sf::Vector2u GetWindowSize() const;
		sf::View GetWindowView() const;
		
		void setWindowView(const sf::View& l_view);
		void moveView(const sf::Vector2f& l_offset);
		void zoomView(const float l_scale);

	private:
		void Setup(const std::string& title, const sf::Vector2u& size);
		void Create();

		sf::RenderWindow m_window;
		EventManager m_eventManager;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
		bool m_isFocused;

		wv::SharedContext*	m_context;
	};
}