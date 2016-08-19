#include "S_Mouse.h"
#include "SystemManager.h"

S_Mouse::S_Mouse(SystemManager *l_systemMgr): S_Base(System::Mouse, l_systemMgr) {
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Drawable);
	req.TurnOnBit((unsigned int)Component::Position);
	req.TurnOnBit((unsigned int)Component::InteractTime);
	m_requiredComponents.push_back(req);
	req.Clear();

	//	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::PlantTree, this);
	//	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::MoveBy, this);
	wv::EventManager* eventMgr = m_systemManager->getContext()->m_window->GetEventManager();

	eventMgr->AddCallback("clickLeft", &S_Mouse::Interact, this);
}
S_Mouse::~S_Mouse() {}

void S_Mouse::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (l_event == EntityEvent::NewGround) {
	}
}

void S_Mouse::Update(float l_dt) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	for (auto &entity : m_entities){
		C_Position* position
			= m_systemManager->getContext()->m_entityManager->GetComponent<C_Position>(entity,Component::Position);
		sf::RenderWindow* window = m_systemManager->getContext()->m_window->GetRenderWindow();
		sf::Vector2i mousePixels = sf::Mouse::getPosition(*m_systemManager->getContext()->m_window->GetRenderWindow());
		sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);
		sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
		position->setPosition(mouseCoords);
	}
}

void S_Mouse::Notify(const Message &l_message) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (HasEntity(l_message.m_receiver)) {
		EntityMessage m = (EntityMessage)l_message.m_type;
		switch (m) {
		case EntityMessage::MakePlantable:
		{
		}
		break;
		}
	}
}

void S_Mouse::Interact(wv::EventDetails* l_details) {
	EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (l_details->m_name == "clickLeft") {
		sf::RenderWindow* window = m_systemManager->getContext()->m_window->GetRenderWindow();
		sf::Vector2i mousePixels = sf::Mouse::getPosition(*m_systemManager->getContext()->m_window->GetRenderWindow());
		sf::Vector2f mousePos = window->mapPixelToCoords(mousePixels);
		sf::Vector2i mouseCoords = wv::Drawable::mapPixelToCoords(mousePos);
		C_Drawable* drawable
			= entities->GetComponent<C_Drawable>(m_entities.front(), Component::Drawable);
		if (drawable->getDrawableName() == "empty") {
			int entity0 = entities->getEntityByCoords(mouseCoords);
			if (entity0 == -1) { return; }
			C_Plantable* plantable
				= entities->GetComponent<C_Plantable>(entity0, Component::Plantable);
			if (plantable->getType() != C_Plantable::Type::Water) {
				m_systemManager->AddEvent(entity0, (EventId)EntityEvent::NewWater);
			}
		}
		
	}
}