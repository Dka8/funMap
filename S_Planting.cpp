#include "S_Planting.h"
#include "SystemManager.h"

S_Planting::S_Planting(SystemManager *l_systemMgr)
	: S_Base(System::Planting, l_systemMgr){
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Position);
	req.TurnOnBit((unsigned int)Component::Plantable);
	m_requiredComponents.push_back(req);
	req.Clear();

//	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::PlantTree, this);
//	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::MoveBy, this);
}
S_Planting::~S_Planting(){}

void S_Planting::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (l_event == EntityEvent::NewGround) {
		std::list<int> entitiesAround = getEntitiesAround(l_entity);
		C_Plantable* plantable
			= entities->GetComponent<C_Plantable>(l_entity, Component::Plantable);
		for (auto& entityAround : entitiesAround) {
			C_Plantable* plantableAround
				= entities->GetComponent<C_Plantable>(entityAround, Component::Plantable);
			if (plantableAround->getType() == C_Plantable::Type::Water) {
				plantable->setType(C_Plantable::Type::Ground);
				Message msg((MessageType)EntityMessage::UpdateTile);
				msg.m_receiver = l_entity;
				msg.m_int = 2;
				m_systemManager->GetMessageHandler()->Dispatch(msg);
			}
		}
	}
	if (l_event == EntityEvent::NewWater) {
		C_Plantable* plantable
			= entities->GetComponent<C_Plantable>(l_entity, Component::Plantable);
		std::list<int> entitiesAround = getEntitiesAround(l_entity);
		for (auto& entityAround : entitiesAround) {
			C_Plantable* plantableAround
				= entities->GetComponent<C_Plantable>(entityAround, Component::Plantable);
			if (plantableAround->getType() == C_Plantable::Type::Water) {
				plantable->setType(C_Plantable::Type::Water);
				Message msg((MessageType)EntityMessage::UpdateTile);
				msg.m_receiver = l_entity;
				msg.m_int = 0;
				m_systemManager->GetMessageHandler()->Dispatch(msg);
			}
		}
		//onNewMap();
	}
}

void S_Planting::Update(float l_dt) {}

void S_Planting::Notify(const Message &l_message) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (HasEntity(l_message.m_receiver)) {
		EntityMessage m = (EntityMessage)l_message.m_type;
		switch (m) {
		/*case EntityMessage::PlantTree:
		{
			C_Plantable* plantable
				= entities->GetComponent<C_Plantable>(l_message.m_receiver, Component::Plantable);
			if (plantable->isPlantable()&&(plantable->getLevel()>=0)) {
				int newTree = entities->AddEntity(l_message.m_entityType);
				if (newTree == -1) { return; }
				plantable->treePlanted();
				C_Position* positionNewTree
					= entities->GetComponent<C_Position>(newTree, Component::Position);
				positionNewTree->setPosition(l_message.m_2f.m_x, l_message.m_2f.m_y);
				m_systemManager->AddEvent(l_message.m_receiver, (EventId)EntityEvent::TreePlanted);
			}
		}
		break;*/
		case EntityMessage::MakePlantable:
		{
			C_Plantable* plantable
				= entities->GetComponent<C_Plantable>(l_message.m_receiver, Component::Plantable);
			plantable->setPlantable(true);
		}
		break;
		}
	}
}
std::list<int> S_Planting::getEntitiesAround(const EntityId l_entity) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	auto positionComp = entities->GetComponent<C_Position>(l_entity, Component::Position);
	sf::Vector2i coords = positionComp->getPosition();
	std::list<int> entitiesAround, entitiesAroundTemp;
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x, coords.y - 1)));
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x + 1, coords.y - 1)));
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x - 1, coords.y)));
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x + 1, coords.y)));
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x - 1, coords.y + 1)));
	entitiesAroundTemp.push_back(entities->getEntityByCoords(sf::Vector2i(coords.x, coords.y + 1), 0));
	for (auto &entity : entitiesAroundTemp) {
		if (entity == -1) { continue; }
		entitiesAround.push_back(entity);
	}
	return entitiesAround;
}
void S_Planting::onNewMap() {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	for (auto& entity : m_entities) {
		C_Plantable* plantable
			= entities->GetComponent<C_Plantable>(entity, Component::Plantable);
		if (plantable->getType() == C_Plantable::Type::Water) {
			m_systemManager->AddEvent(entity, (EventId)EntityEvent::NewGround);
		}
	}
}
