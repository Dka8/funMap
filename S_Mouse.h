#ifndef S_MOUSE_H
#define S_MOUSE_H
#include "S_Base.h"
#include "EventManager.h"

class S_Mouse : public S_Base {
public:
	S_Mouse(SystemManager *l_systemMgr);
	~S_Mouse();

	void Update(float l_dt);
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
	void Notify(const Message &l_message);

	void Interact(wv::EventDetails* l_details);

private:
	EntityId			m_tile;
	C_Plantable::Type	m_newTileType;
};

#endif // !S_Renderer_H
