#ifndef WV_DRAWABLE_H
#define WV_DRAWABLE_H
#include <SFML\Graphics.hpp>
#include "HexaIso.h"
#include "json.hpp"

namespace wv {
	class DrawableType : public sf::Drawable {
	public:
		virtual ~DrawableType() {}
		//virtual void loadDrawable(const nlohmann::json& l_json,
		//	utils::ResourceManager<sf::Texture, std::string>* l_textureMgr) = 0;
		virtual void draw(sf::RenderTarget& l_target, sf::RenderStates l_states) const override = 0;
		//virtual void setTexture(const sf::Texture* l_texture) = 0;
		//virtual void setTextureRect(const sf::IntRect& l_rect) = 0;
	};

	class Sprite : public wv::DrawableType {
	public:
		Sprite(const nlohmann::json& l_json,
			utils::ResourceManager<sf::Texture, std::string>* l_textureMgr) {
			try
			{
				std::string spriteTexture;
				//tileName = l_json["name"].get<std::string>();
				spriteTexture = l_json["texture"].get<std::string>();
				m_sprite.setTexture(l_textureMgr->getOrLoad(spriteTexture, spriteTexture));
			}
			catch (...) {}
			try
			{
				sf::IntRect spriteTextureRect;
				spriteTextureRect = sf::IntRect::Rect(l_json["x"].get<int>(), l_json["y"].get<int>(),
					l_json["width"].get<int>(), l_json["height"].get<int>());
				m_sprite.setTextureRect(spriteTextureRect);
			}
			catch (...) {}
			m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height);

		};

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
	private:
		sf::Sprite		m_sprite;
	};
}

namespace wv {
	class Tile : public wv::DrawableType {
	public:
		Tile(const nlohmann::json& l_json,
			utils::ResourceManager<sf::Texture, std::string>* l_textureMgr)
		{
			m_shape = geometry::HexaIso::getShape();
			m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
			m_shape.setOutlineThickness(2.f / geometry::HexaIso::getScale());
			m_shape.setScale(geometry::HexaIso::getScale(), geometry::HexaIso::getScale());
			try
			{
				std::string tileTexture;
				//tileName = l_json["name"].get<std::string>();
				tileTexture = l_json["texture"].get<std::string>();
				m_shape.setTexture(&l_textureMgr->getOrLoad(tileTexture, tileTexture));
			}
			catch (...) {}
			try
			{
				sf::IntRect tileTextureRect;
				tileTextureRect = sf::IntRect::Rect(l_json["x"].get<int>(), l_json["y"].get<int>(),
					l_json["width"].get<int>(), l_json["height"].get<int>());
				m_shape.setTextureRect(tileTextureRect);
			}
			catch (...) {}
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

	private:
		sf::ConvexShape		m_shape;
	};

	class Mouse : public wv::DrawableType {
	public:
		Mouse(const nlohmann::json& l_json,
			utils::ResourceManager<sf::Texture, std::string>* l_textureMgr)
		{
			m_shape = geometry::HexaIso::getShape();
			m_shape.setScale(geometry::HexaIso::getScale(), geometry::HexaIso::getScale());
			try
			{
				int alphaChannel = 10;
				alphaChannel = l_json["alpha"].get<int>();
				m_shape.setFillColor(sf::Color(0, 0, 0, alphaChannel));
				
			}
			catch (...) {}			
		};

		void draw(sf::RenderTarget& l_target, sf::RenderStates l_states) const {
			l_target.draw(m_shape, l_states);
		};

	private:
		sf::ConvexShape		m_shape;
	};
}

namespace wv {

	class Drawable : public sf::Drawable {
	public:
		Drawable(const nlohmann::json& l_json,
			utils::ResourceManager<sf::Texture, std::string>* l_textureMgr) : m_drawable(nullptr)
		{
			std::string objectType = l_json["type"].get<std::string>();
			if (objectType == "tile") {
				m_drawable = new Tile(l_json, l_textureMgr);
			}
			else if (objectType == "sprite") {
				m_drawable = new Sprite(l_json, l_textureMgr);
			}
			else if (objectType == "mouse") {
				m_drawable = new Mouse(l_json, l_textureMgr);
			}
		};
		virtual ~Drawable() {};

		static sf::Vector2i mapPixelToCoords(float l_x, float l_y) {
			return geometry::HexaIso::mapPixelToCoords(l_x, l_y);
		}
		static sf::Vector2i mapPixelToCoords(const sf::Vector2f& l_pos) {
			return geometry::HexaIso::mapPixelToCoords(l_pos.x, l_pos.y);
		}

		static sf::Vector2f mapCoordsToPixel(int l_x, int l_y) {
			return geometry::HexaIso::mapCoordsToPixel(l_x, l_y);
		}
		static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& l_pos) {
			return geometry::HexaIso::mapCoordsToPixel(l_pos.x, l_pos.y);
		}
		static float getScale() { return geometry::HexaIso::getScale(); }
		
		virtual void loadDrawable(wv::DrawableType* l_drawable) { m_drawable = l_drawable; }

		void Drawable::setCoords(int l_x, int l_y) {
			sf::Vector2f pos = mapCoordsToPixel(l_x, l_y);
			setPosition(pos);
		}

		void Drawable::setCoords(const sf::Vector2i& l_coords) {
			sf::Vector2f pos = mapCoordsToPixel(l_coords);
			setPosition(pos);
		}
		void setPosition(float l_x, float l_y) {
			m_transform.setPosition(l_x, l_y);
		}
		void setPosition(const sf::Vector2f& l_pos) {
			m_transform.setPosition(l_pos);
		}
		void draw(sf::RenderTarget& l_target, sf::RenderStates l_states) const override {
			m_drawable->draw(l_target, m_transform.getTransform());
		}

	private:
		sf::Transformable	m_transform;
		wv::DrawableType*	m_drawable;
	};
}

#endif // !1