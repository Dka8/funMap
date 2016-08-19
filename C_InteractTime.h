#ifndef MAP_C_INTERACTTIME_H
#define MAP_C_INTERACTTIME_H
#include <SFML\System.hpp>
#include "C_Base.h"
#include "C_Timer.h"

class C_InteractTime : public C_Timer {
public:
	C_InteractTime() : C_Timer(Component::InteractTime) {
		m_isBusy = false;
	}
	~C_InteractTime() {}

	void readIn(const nlohmann::json &l_json) override {
		m_time = l_json["time"].get<float>();
	}
	bool isDone() {
		m_timer = m_clock.getElapsedTime();
		if (m_timer.asSeconds() > m_time) {
			m_isBusy = false;
			return true;
		}
		return false;
	}
	
private:
	float	m_time;
};

#endif // !MAP_C_POSITION_H