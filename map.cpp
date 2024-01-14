#include "map.h"
#include<iostream>

void Map::initMap() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || j == 0 || j == width - 1 || i == height - 1) {
				map[i][j] = '#';
			}
			else {
				map[i][j] = ' ';
			}
			MAP.push_back(map[i][j]);
		}
		MAP.push_back('\n');
	}
}

void Map::mapDraw() const {
	std::cout << MAP;
}