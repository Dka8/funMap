#ifndef MAP_C_TIMER_H
#define MAP_C_TIMER_H
#include <SFML\System.hpp>
#include "C_Base.h"

class C_Timer : public C_Base {
public:
	C_Timer(const Component& l_type) : C_Base(l_type){}
	virtual  ~C_Timer() {};

	virtual void readIn(const nlohmann::json &l_json) = 0;

	void restartClock() { 
		m_timer = m_clock.restart();
		m_isBusy = true;
	}
	sf::Time getTime() { return m_timer = m_clock.getElapsedTime(); }
	virtual bool isDone() = 0;

protected:
	sf::Clock	m_clock;
	sf::Time	m_timer;
	bool		m_isDone;
	bool		m_isBusy;
};

#endif // !MAP_C_POSITION_H