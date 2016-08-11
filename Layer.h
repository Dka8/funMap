#ifndef WV_LAYER_H
#define WV_LAYER_H
#include <list>
#include <unordered_map>
#include "SharedContext.h"
#include "json.hpp"

namespace wv {
	
	enum class LayerType{
		BackGround = 0, Ground
	};

	
	using Object = std::pair<std::string, sf::Vector2i>;
	using Objects = std::list<Object*>;

	class Layer {
	public:
		Layer(const Layer&) = delete;
		Layer& operator = (const Layer&) = delete;

		Layer(wv::SharedContext* l_context, const nlohmann::json& l_json);
		~Layer();

		void loadFromJson(const nlohmann::json& json);
		void addItem(const nlohmann::json& l_json);
		void addObject(const nlohmann::json& l_json, bool isSort = false);
		//void sort();
		void draw();

		LayerType getLayerType();
	private:
		void stringToLayerType(const std::string& l_type);
		
		LayerType			m_type;
		Objects				m_objects;
		wv::SharedContext*	m_context;
	};
}

#endif // !MAP_LAYER_H