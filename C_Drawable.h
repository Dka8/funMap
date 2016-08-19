#ifndef MAP_C_DRAWABLE_H
#define MAP_C_DRAWABLE_H
#include "C_Base.h"

class C_Drawable : public C_Base {
public:
	C_Drawable() : C_Base(Component::Drawable), m_drawable(nullptr), m_drawableName("noname") {}
	~C_Drawable() {}

	void readIn(const nlohmann::json &l_json) override {
		m_drawableName = l_json["drawable"].get<std::string>();
	}

	std::string getDrawableName() const { return m_drawableName; }
	
	void setDrawable(std::string l_name, wv::Drawable* l_drawable) {
		m_drawableName = l_name;
		m_drawable = l_drawable;
	}
	wv::Drawable* getDrawable() const {
		if (m_drawable) {
			return m_drawable;
		}
		else {
			std::cout << "cannot return drawable " << m_drawableName << std::endl;
		}
	}

private:
	std::string			m_drawableName;
	wv::Drawable*		m_drawable;
};

#endif // !MAP_C_DRAWABLE_H