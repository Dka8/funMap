#pragma once
#ifndef S_Position_H
#define S_Position_H
#include "S_Base.h"

class S_Position : public S_Base
{
public:
	S_Position(SystemManager *l_systemMgr);
	~S_Position();

	void Update(float l_dt);
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
	void Notify(const Message &l_message);
};

#endif // !S_Position_H