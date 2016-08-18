#ifndef MAP_C_Z_H
#define MAP_C_Z_H

#include <SFML\Graphics.hpp>
#include "C_Base.h"

class C_Z : public C_Base {
public:
	C_Z() : C_Base(Component::Z) {}
	~C_Z() {}

	//void ReadIn(std::stringstream &l_stream) {
	//	l_stream >> m_position.x >> m_position.y;
	//}

	void ReadIn(nlohmann::json &l_json) {
		m_z = l_json["z"].get<int>();
	}

	const int getZ() const { return m_z; }

private:
	int m_z;
};

#endif // !MAP_C_POSITION_H