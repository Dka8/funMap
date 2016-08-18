#ifndef SystemManager_H
#define SystemManager_H
#include <unordered_map>
#include "Window.h"
#include "SharedContext.h"
////#include "EntityManager.h"
#include "EventQueue.h"
//#include "MessageHandler.h"
#include "S_Renderer.h"
#include "S_Position.h"


using SystemContainer = std::unordered_map<System, S_Base*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;
//
//class EntityManager;
class SystemManager {
public:
	SystemManager(wv::SharedContext* l_context);
	~SystemManager();

//	MessageHandler* GetMessageHandler();
//
	void AddEvent(const EntityId &l_entity, const EventId &l_event);
//
	void Update(float l_dt);
	void HandleEvents();
	void Draw();
//	
	void EntityModified(const EntityId &l_entity, const Bitmask &l_bits);
	void RemoveEntity(const EntityId &l_entity);

	void PurgeEntities();
	void PurgeSystems();

	template<class T>
	T* GetSystem(const System l_system) {
		auto itr = m_systems.find(l_system);
		return (itr != m_systems.end() ? dynamic_cast<T*>(itr->second) : nullptr);
	}
	wv::SharedContext* getContext();
private:
	SystemContainer			m_systems;
	EntityEventContainer	m_events;
//	MessageHandler			m_messages;
//
	wv::SharedContext*			m_context;
};
//
#endif // !SystemManager_H

