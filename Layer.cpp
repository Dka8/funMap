#include "Layer.h"

namespace map {

	Layer::Layer(const int l_z, const int l_tileSize)
		: VLayer(l_z,l_tileSize) {}
	Layer::~Layer() {};

	void Layer::loadFromJson(const nlohmann::json& l_json) {
		std::string texture = l_json["texture"].get<std::string>();
		m_texture.loadFromFile(texture);

		nlohmann::json types = l_json["types"];
		for (auto &type : types) {
			std::string name = type["name"].get<std::string>();
			sf::IntRect rect(type["x"].get<int>(), type["y"].get<int>(),
				type["width"].get<int>(), type["height"].get<int>());
			Tile* tile = new Tile(getTileSize());
			tile->setTexture(&m_texture);
			tile->setTextureRect(rect);
			m_types.emplace(name, tile);
		}

		nlohmann::json tiles = l_json["tiles"];
		for (auto &tile : tiles) {
			std::string type = tile["type"].get<std::string>();
			sf::Vector2i pos = sf::Vector2i(tile["x"].get<int>(), tile["y"].get<int>());
			Object* object = new Object(std::make_pair(type, pos));
			m_tiles.push_back(object);
		}
	}

	void Layer::draw(sf::RenderTarget& l_target, sf::RenderStates l_states) {
		for (auto &tile : m_tiles) {
			auto type = m_types[tile->first];
			sf::Vector2i coord = tile->second;
			type->setCoords(coord);
			type->draw(l_target, l_states);
		}
	}
}