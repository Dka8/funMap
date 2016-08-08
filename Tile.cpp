#include "Tile.h"

namespace map {

	Tile::Tile(float l_scale) {
		m_shape = geometry::HexaIso::getShape();

		m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
		m_shape.setOutlineThickness(2.f / l_scale);

		m_shape.setScale(l_scale, l_scale);
	}

	Tile::Tile(int l_posX, int l_posY, float l_scale) {
		m_shape = geometry::HexaIso::getShape();

		m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
		m_shape.setOutlineThickness(2.f / l_scale);

		m_shape.setScale(l_scale, l_scale);
		setCoords(l_posX, l_posY);
	}

	Tile::~Tile(){}

	sf::Vector2i Tile::mapPixelToCoords(float l_x, float l_y, float l_scale) {
		return geometry::HexaIso::mapPixelToCoords(l_x, l_y, l_scale);
	}

	sf::Vector2i Tile::mapPixelToCoords(const sf::Vector2f& l_pos, float l_scale) {
		return geometry::HexaIso::mapPixelToCoords(l_pos.x, l_pos.y, l_scale);
	}

	sf::Vector2f Tile::mapCoordsToPixel(int l_x, int l_y, float l_scale) {
		return geometry::HexaIso::mapCoordsToPixel(l_x, l_y, l_scale);
	}

	sf::Vector2f Tile::mapCoordsToPixel(const sf::Vector2i& l_pos, float l_scale) {
		return geometry::HexaIso::mapCoordsToPixel(l_pos.x, l_pos.y, l_scale);
	}

	void Tile::setCoords(int l_x, int l_y) {
		sf::Vector2f pos = mapCoordsToPixel(l_x,l_y,m_shape.getScale().x);
		m_shape.setPosition(pos);
	}

	void Tile::setCoords(const sf::Vector2i& l_coords) {
		sf::Vector2f pos = mapCoordsToPixel(l_coords, m_shape.getScale().x);
		m_shape.setPosition(pos);
	}

	void Tile::draw(sf::RenderTarget& l_target,
		sf::RenderStates l_states) const {
		l_target.draw(m_shape, l_states);
	}

	void Tile::setTexture(const sf::Texture* l_texture) {
		m_shape.setTexture(l_texture);
	}

	void Tile::setTextureRect(const sf::IntRect& l_rect) {
		m_shape.setTextureRect(l_rect);
	}
}
