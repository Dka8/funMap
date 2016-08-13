#ifndef WV_LAYER_H
#define WV_LAYER_H
#include <list>
#include <unordered_map>
#include "SharedContext.h"
#include "json.hpp"
#include "Drawable.h"

namespace wv {
	
	using LayerId = unsigned int short;
	
	using Object = std::pair<wv::Drawable*, sf::Vector2i>;
	using Objects = std::list<Object*>;

	class Layer {
	public:
		Layer(const Layer&) = delete;
		Layer& operator = (const Layer&) = delete;

		Layer(wv::SharedContext* l_context, const nlohmann::json& l_json);
		~Layer();

		void loadFromJson(const nlohmann::json& json);
		void addItem(const nlohmann::json& l_json, bool isSort = false);
		//void sort();
		void draw();

		LayerId getLayerId();
	private:
		
		LayerId				m_z;
		Objects				m_items;
		wv::SharedContext*	m_context;
	};
}

#endif // !MAP_LAYER_H