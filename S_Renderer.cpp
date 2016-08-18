#include "S_Renderer.h"
#include "SystemManager.h"

S_Renderer::S_Renderer(SystemManager *l_systemMgr)
	: S_Base(System::Renderer, l_systemMgr) {
	Bitmask req;
	req.TurnOnBit((unsigned int)Component::Drawable);
	m_requiredComponents.push_back(req);
	req.Clear();

	//m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::NewBullet, this);
}

S_Renderer::~S_Renderer(){}

void S_Renderer::Update(float dt) {
//	//EntityManager* entities = m_systemManager->GetEntityManager();
//	//for (auto &entity : m_entities) {
//	//	C_Position *position = entities->GetComponent<C_Position>(entity, Component::Position);
//	//	C_Drawable *drawable = nullptr;
//	//
//	//	if(entities->HasComponent(entity,Component::Sprite)){
//	//		drawable = entities->GetComponent<C_Drawable>(entity, Component::Sprite);
//	//	}
//	//	else { continue; }
//	//	drawable->UpdatePosition(position->GetPosition());
//	//}	
}

void S_Renderer::HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) {
	//EntityManager* entities = m_systemManager->getContext()->m_entityManager;
	if (l_event == EntityEvent::TreePlanted) {
		sort();
//		C_Drawable *drawable = entities->GetComponent<C_Drawable>(l_entity, Component::Drawable);
//		std::string drawableName = drawable->getDrawableName();
//		wv::Drawable* drawablePrt = m_systemManager->GetEntityManager()
//			->GetDrawableManager()->getDrawable(drawableName);
//		if (drawablePrt) {
//			drawable->setDrawable(drawablePrt);
//		}
//		C_Position *position = entities->GetComponent<C_Position>(l_entity, Component::Position);
//		position->SetPosition(10, 10);
	}
}
//
void S_Renderer::Notify(const Message &l_message) {
//	//EntityManager* entities = m_systemManager->GetEntityManager();
//	//if (HasEntity(l_message.m_receiver)) {
//	//	EntityMessage m = (EntityMessage)l_message.m_type;
//	//	switch (m) {
//	//	
//	//	}
//	//}
}

void S_Renderer::Render() {
	sf::RenderWindow* window = m_systemManager->getContext()->m_window->GetRenderWindow();
	sf::View windowView = window->getView();

	sf::FloatRect viewRect = sf::FloatRect(windowView.getCenter().x - windowView.getSize().x / 2.f,
		windowView.getCenter().y - windowView.getSize().y / 2.f,
		windowView.getSize().x, windowView.getSize().y);	
	
	EntityManager *entities = m_systemManager->getContext()->m_entityManager;
	for (auto &entity : m_entities) {
		C_Drawable *drawable = nullptr;
		if (!entities->HasComponent(entity, Component::Drawable)) { continue; }
		drawable = entities->GetComponent<C_Drawable>(entity, Component::Drawable);
		if (entities->HasComponent(entity, Component::Position)) {
			C_Position* positionComponent = entities->GetComponent<C_Position>(entity, Component::Position);
			sf::Vector2i itemCoord = positionComponent->getPosition();
			sf::Vector2f itemPos = wv::Drawable::mapCoordsToPixel(itemCoord);
			if ((itemPos.x > (viewRect.left - wv::Drawable::getScale())
				&& itemPos.x < (viewRect.left + viewRect.width + wv::Drawable::getScale()))
				&& (itemPos.y >(viewRect.top - wv::Drawable::getScale())
					&& itemPos.y < (viewRect.top + viewRect.height + wv::Drawable::getScale()))) {
				wv::Drawable* item = nullptr;
				item = drawable->getDrawable();
				if (item) {
					item->setPosition(itemPos);
					window->draw(*(item));
				}
			}
		}

	}
}
void S_Renderer::sort() {
	EntityManager* e_mgr = m_systemManager->getContext()->m_entityManager;
	std::sort(m_entities.begin(), m_entities.end(),
		[e_mgr](const EntityId& entity1, const EntityId& entity2) {
		C_Position* positionC1 = e_mgr->GetComponent<C_Position>(entity1, Component::Position);
		C_Position* positionC2 = e_mgr->GetComponent<C_Position>(entity2, Component::Position);
		
		if (positionC1->getZ() == positionC2->getZ()) {
			if (positionC1->getPosition().y == positionC2->getPosition().y) {
				return (positionC1->getPosition().x < positionC2->getPosition().x);
			}
			return (positionC1->getPosition().y < positionC2->getPosition().y);
		}
		return (positionC1->getZ() < positionC2->getZ());
	});
}