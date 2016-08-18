#ifndef MAP_C_PLANTABLE_H
#define MAP_C_PLANTABLE_H
#include "C_Base.h"

class C_Plantable : public C_Base {
public:
	C_Plantable() : C_Base(Component::Plantable) {}
	~C_Plantable() {}

	void readIn(const nlohmann::json &l_json) override {
		m_plantable = l_json["plantable"].get<int>();
	}

	const bool isPlantable() const { return m_plantable; }
	void treePlanted() { m_plantable = false; }
	void treeRemoved() { m_plantable = true; }
	
private:
	bool	m_plantable;
};

#endif // !MAP_C_POSITION_H