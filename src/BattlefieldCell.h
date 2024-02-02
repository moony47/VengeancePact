#pragma once
#include <vector>
#include "Agent.h"
#include "TerrainTile.h"
#include "Scenery.h"

#include "SFML/Graphics.hpp"

struct MapCell {
    int x, y;
    TerrainTile terrain;
    sf::Texture* texture;

    std::vector<Scenery*> scenery;
};