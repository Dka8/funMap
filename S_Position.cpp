#include "S_Position.h"
#include "SystemManager.h"

S_Position::S_Position(SystemManager *l_systemMgr)
	: S_Base(System::Position, l_systemMgr){
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Position);
	m_requiredComponents.push_back(req);
	req.Clear();

//	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::SetPosition, this);
//	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::MoveBy, this);
}
S_Position::~S_Position(){}

void S_Position::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (l_event == EntityEvent::Spawned) {
		C_Position *position = entities->GetComponent<C_Position>(l_entity, Component::Position);

		sf::RenderWindow* window = m_systemManager->getContext()->m_window->GetRenderWindow();
		sf::Vector2i mousePixels = sf::Mouse::getPosition(*window);
		sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);

		sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
		position->SetPosition(mouseCoords.x, mouseCoords.y);
	}
}

void S_Position::Update(float l_dt) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	for (auto& entity : m_entities) {
		C_Position* pos = entities->GetComponent<C_Position>(entity, Component::Position);
	}
}
void S_Position::Notify(const Message &l_message) {
//	/*EntityManager* entities = m_systemManager->GetEntityManager();
//	if (HasEntity(l_message.m_receiver)) {
//		EntityMessage m = (EntityMessage)l_message.m_type;
//		switch (m) {
//		case EntityMessage::SetPosition:
//		{
//			C_Position *position = entities->GetComponent<C_Position>(l_message.m_receiver, Component::Position);
//			position->SetPosition(l_message.m_2f.m_x, l_message.m_2f.m_y);			
//		}
//		break;
//		case EntityMessage::MoveBy:
//		{
//			C_Position *position = entities->GetComponent<C_Position>(l_message.m_receiver, Component::Position);
//			position->MoveBy(l_message.m_2f.m_x, l_message.m_2f.m_y);
//		}
//		break;
//		}
//	}*/
}
