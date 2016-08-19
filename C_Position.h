#ifndef MAP_C_POSITION_H
#define MAP_C_POSITION_H

#include <SFML\Graphics.hpp>
#include "C_Base.h"

class C_Position : public C_Base {
public:
	C_Position() : C_Base(Component::Position) {}
	~C_Position() {}

	void readIn(const nlohmann::json &l_json) override{
		m_position.x = l_json["x"].get<int>();
		m_position.y = l_json["y"].get<int>();
		m_z = l_json["z"].get<int>();
	}
	
	const float getZ() const { return m_z; }
	const sf::Vector2i& getPosition() const { return m_position; }
	const sf::Vector2i& getPositionOld() const { return m_positionOld; }

	void setPosition(int l_x, int l_y) {
		m_positionOld = m_position;
		m_position = sf::Vector2i(l_x, l_y);
	}
	void setPosition(sf::Vector2i l_pos) {
		m_positionOld = m_position;
		m_position = l_pos;
	}

private:
	float			m_z;
	sf::Vector2i	m_position;
	sf::Vector2i	m_positionOld;
};

#endif // !MAP_C_POSITION_H