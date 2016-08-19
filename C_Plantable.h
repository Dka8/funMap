#ifndef MAP_C_PLANTABLE_H
#define MAP_C_PLANTABLE_H
#include "C_Base.h"

class C_Plantable : public C_Base {
public:
	enum class Type {
		Water = 0, Sand, Ground
	};

	C_Plantable() : C_Base(Component::Plantable) {}
	~C_Plantable() {}

	void readIn(const nlohmann::json &l_json) override {
		std::string type = l_json["type"].get<std::string>();
		if (type == "water") { m_type = Type::Water; }
		else if (type == "sand") { m_type = Type::Sand; }
		else { m_type = Type::Ground; }
		m_plantable = l_json["plantable"].get<int>();
		m_level = l_json["level"].get<int>();
	}
	void setType(const Type l_type) {
		m_type = l_type;
		resetLevel();
		if (m_type == Type::Ground) { m_plantable = true; }
		else { m_plantable = false; }
	}
	Type getType() { return m_type; }

	const bool isPlantable() const { return m_plantable; }
	void setPlantable(const bool l_plantable) { m_plantable = l_plantable; }
	void treePlanted() { m_plantable = false; }
	void treeRemoved() { m_plantable = true; }

	void levelUp() {
		++m_level;
	}
	void resetLevel() { m_level = 0; }
	void setLevel(int l_tire) { m_level = l_tire; }
	int getLevel() const { return m_level; }
	
private:
	Type	m_type;
	bool	m_plantable;
	int		m_level;
};

#endif // !MAP_C_POSITION_H