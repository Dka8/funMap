#ifndef MAP_LAYER_H
#define MAP_LAYER_H
#include "VLayer.h"
#include "Tile.h"
#include <list>
#include <unordered_map>

namespace map {
	
	using Vocabulary = std::unordered_map<std::string, Tile*>;
	using Object = std::pair<std::string, sf::Vector2i>;
	using Objects = std::list<Object*>;

	class Layer : public VLayer {
	public:
		Layer(const Layer&) = delete;
		Layer& operator = (const Layer&) = delete;

		Layer(const int z, const int tileSize);

		~Layer();
		//void sort() override;
		void loadFromJson(const nlohmann::json& json) override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	private:
		
		Vocabulary		m_types;
		Objects			m_tiles;
		sf::Texture		m_texture;
	};
}

#endif // !MAP_LAYER_H