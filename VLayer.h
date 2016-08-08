#ifndef MAP_VLAYER_H
#define MAP_VLAYER_H
#include <SFML\Graphics.hpp>
#include "json.hpp"

namespace map {
	
	class VLayer {
	public:
		VLayer(const VLayer&) = delete;
		VLayer& operator = (const VLayer&) = delete;

		VLayer(const int l_z, const int l_tileSize)
			: m_z(l_z), m_tileSize(l_tileSize){}
		virtual ~VLayer() {};
		//virtual void sort() = 0;
		virtual void loadFromJson(const nlohmann::json& json) = 0;

		int z() const { return m_z; }
		int getTileSize()const { return m_tileSize; }
	
	protected:

	private:
		const int m_z;
		const int m_tileSize;
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	};
}

#endif // !MAP_VLAYER_H