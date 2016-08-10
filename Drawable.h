#ifndef WV_DRAWABLE_H
#define WV_DRAWABLE_H
#include <SFML\Graphics.hpp>
#include "HexaIso.h"

namespace wv {

	class Drawable : public sf::Drawable, public sf::Transformable {
	public:
		virtual ~Drawable() {};

		static float getScale() { return m_scale; }
		static void setScale(float l_scale) { m_scale = l_scale; }
		static sf::Vector2i mapPixelToCoords(float l_x, float l_y) {
			return geometry::HexaIso::mapPixelToCoords(l_x, l_y, m_scale);
		}
		static sf::Vector2i mapPixelToCoords(const sf::Vector2f& l_pos) {
			return geometry::HexaIso::mapPixelToCoords(l_pos.x, l_pos.y, m_scale);
		}

		static sf::Vector2f mapCoordsToPixel(int l_x, int l_y) {
			return geometry::HexaIso::mapCoordsToPixel(l_x, l_y, m_scale);
		}
		static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& l_pos) {
			return geometry::HexaIso::mapCoordsToPixel(l_pos.x, l_pos.y, m_scale);
		}
	
		void Drawable::setCoords(int l_x, int l_y) {
			sf::Vector2f pos = mapCoordsToPixel(l_x, l_y);
			setPosition(pos);
		}

		void Drawable::setCoords(const sf::Vector2i& l_coords) {
			sf::Vector2f pos = mapCoordsToPixel(l_coords);
			setPosition(pos);
		}

	
		virtual void setTexture(const sf::Texture* l_texture) = 0;
		virtual void setTexture(const sf::Texture& l_texture) = 0;
		virtual void setTextureRect(const sf::IntRect& l_rect) = 0;

		virtual void setPosition(float x, float y) = 0;
		virtual void setPosition(const sf::Vector2f& pos) = 0;

	private:
		static float m_scale;
	};
}

namespace wv {
	class Sprite : public Drawable, public sf::Sprite {
	public:
		Sprite() : sf::Sprite() {};

		void setTexture(const sf::Texture* l_texture) {};
		void setTexture(const sf::Texture& l_texture) {
			m_sprite.setTexture(l_texture);
		};
		void setTextureRect(const sf::IntRect& l_rect) {
			m_sprite.setTextureRect(l_rect);
		};
		void draw(sf::RenderTarget& l_target, sf::RenderStates l_states) const {
			l_target.draw(m_sprite, l_states);
		};
		void setPosition(float l_x, float l_y) {
			m_sprite.setPosition(l_x, l_y);
		}
		void setPosition(const sf::Vector2f& l_pos) {
			m_sprite.setPosition(l_pos);
		}
	private:
		sf::Sprite		m_sprite;
	};
}

namespace wv {
	class Tile : public Drawable, public sf::ConvexShape {
	public:
		Tile() {
			m_shape = geometry::HexaIso::getShape();

			m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
			m_shape.setOutlineThickness(2.f / wv::Drawable::getScale());

			m_shape.setScale(wv::Drawable::getScale(), wv::Drawable::getScale());
		};

		void setTexture(const sf::Texture* l_texture) {
			m_shape.setTexture(l_texture);
		};
		void setTexture(const sf::Texture& l_texture) {};
		void setTextureRect(const sf::IntRect& l_rect) {
			m_shape.setTextureRect(l_rect);
		};
		void draw(sf::RenderTarget& l_target, sf::RenderStates l_states) const {
			l_target.draw(m_shape, l_states);
		};
		void setPosition(float l_x, float l_y) {
			m_shape.setPosition(l_x, l_y);
		}
		void setPosition(const sf::Vector2f& l_pos) {
			m_shape.setPosition(l_pos);
		}
	private:
		sf::ConvexShape		m_shape;
	};
}

#endif // !1