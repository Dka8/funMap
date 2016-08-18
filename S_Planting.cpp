#include "S_Planting.h"
#include "SystemManager.h"

S_Planting::S_Planting(SystemManager *l_systemMgr)
	: S_Base(System::Planting, l_systemMgr){
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Position);
	req.TurnOnBit((unsigned int)Component::Plantable);
	m_requiredComponents.push_back(req);
	req.Clear();

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::PlantTree, this);
//	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::MoveBy, this);
}
S_Planting::~S_Planting(){}

void S_Planting::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) {
	//EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	//if (l_event == EntityEvent::Spawned) {
	//	sf::RenderWindow* window = m_systemManager->getContext()->m_window->GetRenderWindow();
	//	sf::Vector2i mousePixels = sf::Mouse::getPosition(*window);
	//	sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);
	//
	//	sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
	//
	//	C_Position *position = entities->GetComponent<C_Position>(l_entity, Component::Position);
	//	position->SetPosition(mouseCoords.x, mouseCoords.y);
	//}
}

void S_Planting::Update(float l_dt) {
	//EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	//for (auto& entity : m_entities) {
	//	C_Position* pos = entities->GetComponent<C_Position>(entity, Component::Position);
	//}
}
void S_Planting::Notify(const Message &l_message) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (HasEntity(l_message.m_receiver)) {
		EntityMessage m = (EntityMessage)l_message.m_type;
		switch (m) {
		case EntityMessage::PlantTree:
		{
			C_Plantable* plantable
				= entities->GetComponent<C_Plantable>(l_message.m_receiver, Component::Plantable);
			if (plantable->isPlantable()) {
				int newTree = entities->AddEntity(l_message.m_entityType);
				if (newTree == -1) { return; }
				plantable->treePlanted();
				C_Position* positionNewTree
					= entities->GetComponent<C_Position>(newTree, Component::Position);
				positionNewTree->setPosition(l_message.m_2f.m_x, l_message.m_2f.m_y);
				m_systemManager->AddEvent(newTree, (EventId)EntityEvent::TreePlanted);
			}
		}
		break;
//		case EntityMessage::MoveBy:
//		{
//			C_Position *position = entities->GetComponent<C_Position>(l_message.m_receiver, Component::Position);
//			position->MoveBy(l_message.m_2f.m_x, l_message.m_2f.m_y);
//		}
//		break;
		}
	}
}
