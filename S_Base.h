#ifndef S_Base_H
#define S_Base_H
#include "EntityManager.h"
#include "Bitmask.h"
#include "ECS_Types.h"
#include "EntityEvent.h"
#include "Observer.h"

using EntityList = std::vector<EntityId>;
using Requirements = std::vector<Bitmask>;

class SystemManager;
class S_Base : public Observer{
public:
	S_Base(const System &l_id, SystemManager *l_systemMgr);
	virtual ~S_Base();
	
	bool AddEntity(const EntityId &l_entity);
	bool HasEntity(const EntityId &l_entity);
	bool RemoveEntity(const EntityId &l_entity);

	System GetId();

	bool FitsRequirements(const Bitmask &l_bits);
	void Purge();

	virtual void Update(float l_dt) = 0;
	virtual void HandleEvent(const EntityId &l_entity, const EntityEvent &l_event) = 0;

	Bitmask& GetBitMask();

protected:
	System			m_id;
	Requirements	m_requiredComponents;
	EntityList		m_entities;

	SystemManager	*m_systemManager;
};

#endif // !S_Base_H

