#include "HexaIso.h"
#include <cmath>
#include <iostream>

namespace geometry {
	namespace math {
		const float PI = 3.14159265;

		const float sin_75 = sin(75 * PI / 180.f);
		const float sin_15 = sin(15 * PI / 180.f);
		const float sin_45 = sin(45 * PI / 180.f);

		const float height = sin_15 + sin_45 + sin_75;
		const float delta_x = sin_45 - sin_15;
		const float delta_y = sin_75 + sin_45;
	}
	using namespace math;

	sf::ConvexShape HexaIso::m_shape;
	float HexaIso::m_scale = 32.f;
	HexaIso::__Initiatiser HexaIso::__initiatiser__;

	const sf::ConvexShape& HexaIso::getShape() { return m_shape; }
	const float HexaIso::getScale() { return m_scale; }

	sf::Vector2f HexaIso::mapCoordsToPixel(int X, int Y) {
		return sf::Vector2f((Y*delta_x + X*delta_y) * m_scale,
			(Y*delta_y / 2 + X*delta_x / 2)*m_scale);
	}

	sf::Vector2i HexaIso::mapPixelToCoords(float X, float Y) {
		const float d_x = delta_x * m_scale;
		const float d_y = delta_y * m_scale;

		const float y = (-X*d_x + 2 * Y*d_y) / (d_y*d_y - d_x*d_x);
		const float x = -(y*d_x - X) / d_y;

		return HexaIso::round(x, y);
	}

	sf::Vector2i HexaIso::round(float x, float y) {
		const float z = -x - y;
		float rx = std::round(x);
		float ry = std::round(y);
		float rz = std::round(z);

		const float diff_x = std::abs(rx - x);
		const float diff_y = std::abs(ry - y);
		const float diff_z = std::abs(rz - z);

		if ((diff_x > diff_y) && (diff_x > diff_z))
			rx = -ry - rz;
		else if (diff_y > diff_z)
			ry = -rx - rz;

		return sf::Vector2i(rx, ry);
	}

	sf::IntRect HexaIso::getTextureRect(int x, int y) {
		sf::Vector2f pos = mapCoordsToPixel(x, y);
		sf::IntRect res(pos.x, pos.y, height * m_scale, height / 2 * m_scale);
		return res;
	}

	int HexaIso::distance(int x1, int y1, int x2, int y2) {
		return std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(x1 + y1 - x2 - y2) / 2;
	}

	void HexaIso::init() {
		std::cout << sin_15 << std::endl;
		m_shape.setPointCount(6);
		m_shape.setPoint(0, sf::Vector2f(0, (sin_15 + sin_75) / 2.f));
		m_shape.setPoint(1, sf::Vector2f(sin_15, sin_15 / 2.f));
		m_shape.setPoint(2, sf::Vector2f(sin_15 + sin_75, 0));
		m_shape.setPoint(3, sf::Vector2f(sin_15 + sin_75 + sin_45, sin_45 / 2.f));
		m_shape.setPoint(4, sf::Vector2f(sin_75 + sin_45, (sin_75 + sin_45) / 2.f));
		m_shape.setPoint(5, sf::Vector2f(sin_45, (sin_15 + sin_75 + sin_45) / 2.f));

		m_shape.setOrigin(height / 2.f, height / 4.f);
	}
}