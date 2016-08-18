#ifndef WV_MAP_H
#define WV_MAP_H
#include <list>
#include <map>
#include "SharedContext.h"
#include "json.hpp"
#include "Drawable.h"

namespace wv {
	
	struct Vector2iComparator
	{
		bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const
		{
			if (a.y != b.y) { return (a.y < b.y); }
			else { return (a.x < b.x); }
		}
	};
	
	using Items = std::map<sf::Vector2i, wv::Drawable*, Vector2iComparator>;

	class Map {
	public:
		Map(const Map&) = delete;
		Map& operator = (const Map&) = delete;

		Map(wv::SharedContext* l_context, const std::string& l_file);
		~Map();

		void loadFromFile(const std::string& l_file);
		void loadFromJson(const nlohmann::json& json);
		void addItem(const nlohmann::json& l_json);
		void draw();

	private:
		
		Items				m_items;
		wv::SharedContext*	m_context;
	};
}

#endif // !MAP_MAP_H