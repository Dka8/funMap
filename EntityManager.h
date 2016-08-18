#ifndef EntityManager_H
#define EntityManager_H
#include <vector>
#include <unordered_map>
#include <functional>
#include "SharedContext.h"
#include "Bitmask.h"
#include "ECS_Types.h"
/////#include "ResourceManager.hpp"
#include "C_Drawable.h"
#include "C_Position.h"
//
using EntityId = unsigned int;
//
using ComponentContainer = std::vector<C_Base*>;
using EntityData = std::pair<Bitmask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;
using ComponentFactory = std::unordered_map<Component, std::function<C_Base*(void)>>;
//using EntityToRemove = std::vector<EntityId>;
//
////class SystemManager;
class EntityManager
{
public:
	EntityManager(wv::SharedContext* l_context);
	~EntityManager();

	void loadEntitiesFromFile(const std::string& l_file);
	void loadEntitiesFromJson(const nlohmann::json& l_json);

	int AddEntity(const Bitmask &l_mask);
	int AddEntity(const std::string &l_entityFile);
	bool RemoveEntity(const EntityId &l_entity);
	
	bool AddComponent(const EntityId &l_entity, const Component &l_component);
	bool RemoveComponent(const EntityId &l_entity, const Component &l_component);
	bool HasComponent(const EntityId &l_entity, const Component &l_component);
//
	template<class T>
	T* GetComponent(const EntityId &l_entity, const Component &l_component) {
		auto itr = m_entities.find(l_entity);
		if (itr == m_entities.end()) { return nullptr; }
		if (!itr->second.first.GetBit((unsigned int)l_component)) { return nullptr; }
		auto &container = itr->second.second;
		auto component = std::find_if(container.begin(), container.end(),
			[&l_component](C_Base* c) {
			return c->getType() == l_component;
		});
		return (component != container.end() ? dynamic_cast<T*>(*component) : nullptr);
	}
//
//	void Purge();

private:
	template<class T>
	void AddComponentType(const Component &l_id) {
		m_cFactory[l_id] = []()->C_Base* {return new T(); };
	}

	unsigned int			m_idCounter;
	EntityContainer			m_entities;
	ComponentFactory		m_cFactory;
	nlohmann::json			m_jsonEntities;
	wv::SharedContext*		m_context;
};

#endif // !EntityManager_H