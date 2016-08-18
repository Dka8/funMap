#include "EntityManager.h"
#include "SystemManager.h"

EntityManager::EntityManager(wv::SharedContext* l_context) : m_context(l_context), m_idCounter(0){

	AddComponentType<C_Drawable>(Component::Drawable);
	AddComponentType<C_Position>(Component::Position);

	loadEntitiesFromFile("entities.json");
}
EntityManager::~EntityManager() { /*Purge();*/ }
void EntityManager::loadEntitiesFromFile(const std::string& l_file) {
	std::ifstream fin;
	fin.open(l_file);
	if (!fin.is_open()) {
		std::cout << "cannot open file " << l_file <<std::endl;
	}
	nlohmann::json data = nlohmann::json::parse(fin);
	loadEntitiesFromJson(data);
}
void EntityManager::loadEntitiesFromJson(const nlohmann::json& l_json) {
	m_jsonEntities = l_json["entities"];
}
//
int EntityManager::AddEntity(const Bitmask &l_mask){
	unsigned int entity = m_idCounter;
	Bitmask bitmask;
	if (!m_entities.emplace(entity, EntityData(bitmask, ComponentContainer())).second) {
		return -1;
	}
	++m_idCounter;
	auto itr = m_entities.find(entity);
	for (unsigned int i = 0; i < MaskLength; ++i) {
		if (l_mask.GetBit(i)) {
			AddComponent(entity, Component(i));
		}
	}
	m_context->m_systemManager->EntityModified(entity, l_mask);
	m_context->m_systemManager->AddEvent(entity, (EventId)EntityEvent::Spawned);
	return entity;
}

int EntityManager::AddEntity(const std::string &l_entityName){
	int entityId = -1;

	for (auto &entity : m_jsonEntities) {
		if (entity["name"].get<std::string>() != l_entityName) { continue; }
		Bitmask mask;
		entity >> mask;
		entityId = AddEntity(mask);
		if (entityId == -1) { return -1; }
		nlohmann::json components = entity["components"];
		for (auto &component : components) {
			int c_id = component["id"].get<int>();
			C_Base* newComponent = GetComponent<C_Base>(entityId, (Component)c_id);
			if (!newComponent) { continue; }
			component >> *newComponent;

			if (newComponent->getType() == Component::Drawable) {
				wv::Drawable* drawable = m_context->m_drawableManager->getDrawable(l_entityName);
				if (!drawable) {
					std::cout << "cannot find drawable for new entity" << std::endl;
				}
				C_Drawable* drawableComponent = (C_Drawable*)newComponent;
				drawableComponent->setDrawable(drawable);
			}
		}
	}
	std::cout << "Add new entity:\n" << entityId << "\t" << l_entityName << std::endl;
	return entityId;
}
bool EntityManager::RemoveEntity(const EntityId &l_entity) {
	auto itr = m_entities.find(l_entity);
	if (itr == m_entities.end()) { return false; }

	while (itr->second.second.begin() != itr->second.second.end()) {
		delete itr->second.second.back();
		itr->second.second.pop_back();
	};
	m_entities.erase(itr);
	m_context->m_systemManager->RemoveEntity(l_entity);
	return true;
}
bool EntityManager::AddComponent(const EntityId & l_entity, const Component &l_component) {
	auto itr = m_entities.find(l_entity);
	if (itr == m_entities.end()) { return false; }
	if (itr->second.first.GetBit((unsigned int)l_component)) { return false; }

	auto itr2 = m_cFactory.find(l_component);
	if (itr2 == m_cFactory.end()) { return false; }
	C_Base* component = itr2->second();
	itr->second.second.emplace_back(component);
	itr->second.first.TurnOnBit((unsigned int)l_component);

	m_context->m_systemManager->EntityModified(l_entity, itr->second.first);
	return true;
}
bool EntityManager::RemoveComponent(const EntityId &l_entity, const Component &l_component) {
	auto itr = m_entities.find(l_entity);
	if (itr == m_entities.end()) { return false; }
	if (!itr->second.first.GetBit((unsigned int)l_component)) { return false; }

	auto &container = itr->second.second;
	auto component = std::find_if(container.begin(), container.end(),
		[&l_component](C_Base *c) {
		return c->getType() == l_component;
	});
	if (component == container.end()) { return false; }
	delete (*component);
	container.erase(component);
	itr->second.first.ClearBit((unsigned int)l_component);

	m_context->m_systemManager->EntityModified(l_entity, itr->second.first);
	return true;
}
bool EntityManager::HasComponent(const EntityId &l_entity, const Component &l_component) {
	auto itr = m_entities.find(l_entity);
	if (itr == m_entities.end()) { return false; }
	return itr->second.first.GetBit((unsigned int)l_component);
}
//
//void EntityManager::Purge() {
//	//m_systems->PurgeEntities();
//
//	for (auto &entity : m_entities) {
//		for (auto &component : entity.second.second) { delete component; }
//		entity.second.second.clear();
//		entity.second.first.Clear();
//	}
//	m_entities.clear();
//	m_idCounter = 0;
//}
