#pragma once

#include<string>

class Map {
private:
	int width = 50;
	int height = 25;
	std::string MAP = "";
	char map[25][50];
public:
	void initMap();

	void mapDraw() const;
};
