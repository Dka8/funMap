#include "Map.h"

namespace wv {

	Map::Map(wv::SharedContext* l_context, const nlohmann::json& l_json): m_context(l_context) {
		nlohmann::json layers = l_json["layers"];
		for (auto &layer : layers) {
			wv::Layer* newLayer = new wv::Layer(m_context, layer);
			if (newLayer)
			{
				m_layers.emplace(newLayer->getLayerId(), newLayer);
			}
		}
	}
	
	Map::~Map(){}

	void Map::draw() {
		for (auto &layer : m_layers) {
			layer.second->draw();
		}
	}
}
