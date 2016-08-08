#ifndef MAP_TILE_H
#define MAP_TILE_H
#include <SFML\Graphics.hpp>
#include "HexaIso.h"
#include "json.hpp"

namespace map {

	class Tile : public sf::Drawable {
	public:
		Tile(const Tile&) = delete;
		Tile& operator = (const Tile&) = delete;

		Tile(Tile&&) = default;
		Tile& operator = (Tile&&) = default;

		Tile(float scale);
		Tile(int pos_x, int pox_y, float scale);
		virtual ~Tile();

		static sf::Vector2i mapPixelToCoords(float x, float y, float scale);
		static sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos, float scale);

		static sf::Vector2f mapCoordsToPixel(int x, int y, float scale);
		static sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos, float scale);


		void setCoords(int x, int y);
		void setCoords(const sf::Vector2i& coords);

		void setTexture(const sf::Texture* texture);
		void setTextureRect(const sf::IntRect& rect);

		virtual void draw(sf::RenderTarget& l_target,
			sf::RenderStates states) const override;
	private:
		sf::ConvexShape		m_shape;		
	};
}

#endif // !MAP_TILE_H