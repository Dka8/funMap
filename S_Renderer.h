#ifndef S_Renderer_H
#define S_Renderer_H
#include "S_Base.h"

class S_Renderer : public S_Base{
public:
	S_Renderer(SystemManager *l_systemMgr);
	~S_Renderer();

	void Update(float l_dt);
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
	void Notify(const Message &l_message);

	void Render();
private:
};

#endif // !S_Renderer_H
