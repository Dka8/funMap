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
	}
	
	const sf::Vector2i& GetPosition() const { return m_position; }
	const sf::Vector2i& GetPositionOld() const { return m_positionOld; }

	void SetPosition(int l_x, int l_y) {
		m_positionOld = m_position;
		m_position = sf::Vector2i(l_x, l_y);
	}
	void SetPosition(sf::Vector2i l_pos) {
		m_positionOld = m_position;
		m_position = l_pos;
	}

private:
	sf::Vector2i m_position;
	sf::Vector2i m_positionOld;
};

#endif // !MAP_C_POSITION_H