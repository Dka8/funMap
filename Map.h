#ifndef WV_MAP_H
#define WV_MAP_H
#include "Layer.h"
#include "SharedContext.h"
#include "json.hpp"
#include <unordered_map>
#include <string>

namespace wv {

	using Layers = std::map<LayerType, wv::Layer*>;

	class Map
	{
	public:
		Map(wv::SharedContext* l_context, const nlohmann::json& l_json);
		~Map();

		void draw();
	private:
		//void addLayer(const nlohmann::json& l_json);


		Layers				m_layers;
		wv::SharedContext*	m_context;
	};

}

#endif // !WV_MAP_H