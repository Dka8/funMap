#include "VLayer.h"
#include "Layer.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>

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
	//srand(time(nullptr));

	/*std::ofstream fout;
	fout.open("tile.txt");

	for (int y = 1; y < 21; ++y) {
		for (int x = 1; x < 21; ++x) {
			fout << "\t\t{ \"type\" :\"" << enumToString(rand() % 1)
				<< "\",\t\"x\" : " << x << ", \"y\" : " << y << "}," << std::endl;
		}
	}
	fout.close();*/

	nlohmann::json json;
	std::ifstream fin;
	fin.open("layer.json");
	if (fin.is_open()) {
		 json = nlohmann::json::parse(fin);
	}
	fin.close();

	map::Layer* layer;
	layer = new map::Layer(1, 32);

	layer->loadFromJson(json);

	sf::RenderWindow window(sf::VideoMode(1600, 900), "Shape");

	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}		
		layer->draw(window, sf::RenderStates::Default);
		window.display();
	}

	return 0;
}