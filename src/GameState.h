#pragma once
#include <vector>
#include "MapCell.h"
#include "QuadTree.h"
#include "Weather.h"

class GameState {
public:
    std::vector<MapCell> cells;
    std::list<Agent> agents;
    QuadTree* quadTree = nullptr;

    Weather weather;
};



