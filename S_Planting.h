#pragma once
#ifndef S_Planting_H
#define S_Planting_H
#include "S_Base.h"
#include <list>

class S_Planting : public S_Base
{
public:
	S_Planting(SystemManager *l_systemMgr);
	~S_Planting();

	void Update(float l_dt);
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
	void Notify(const Message &l_message);

	std::list<int> getEntitiesAround(const EntityId);
	void onNewMap();

private:
};

#endif // !S_Planting_H