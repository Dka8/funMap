//#include "VLayer.h"
//#include "Layer.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include "ItemManager.h"
#include "Drawable.h"

enum class TileType {
	Earth = 0, Sand, Rock
};

std::string enumToString(int l_i) {
	std::string type;
	if (l_i == 0) type = "rock";
	else if (l_i == 1) type = "sand";
	else if (l_i == 2) type = "earth";
	return type;
}

int main() {
	
	nlohmann::json json;
	std::ifstream fin;
	fin.open("layer.json");
	if (fin.is_open()) {
		 json = nlohmann::json::parse(fin);
	}
	fin.close();

	//map::Layer* layer;
	//layer = new map::Layer(1, 32);

	//layer->loadFromJson(json);

	//wv::ItemManager itemManager;
	utils::ResourceManager<sf::Texture, std::string> textureManager;
	wv::ItemManager* itemManager = textureManager.makeItemManager();
	itemManager->setTextureMgr(&textureManager);

	nlohmann::json item;
	item["name"] = "water";
	item["texture"] = "tiles.jpg";
	item["rect"] = { { "x", 0 },{ "y", 0 }, 
						{ "width", 100 },{ "height", 100 } };

	itemManager->addDrawable(wv::DrawableType::Tile, item);

	sf::RenderWindow window(sf::VideoMode(1600, 900), "Shape");

	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//layer->draw(window, sf::RenderStates::Default);
		auto drawable = itemManager->getDrawable("water");
		drawable->setCoords(1, 1);
		window.draw(*drawable);
		window.display();
	}

	return 0;
}