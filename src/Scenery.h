#pragma once
#include "SFML/Graphics.hpp"

struct Scenery {
	float x, y;
	sf::Texture* texture;

	Scenery(float _x, float _y) {
		x = _x;
		y = _y;

		texture = new sf::Texture();
		texture->loadFromFile("resources/images/terrain/scenery/tree.png");
	}
};

