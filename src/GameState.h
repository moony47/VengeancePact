#pragma once
#include <vector>
#include "BattlefieldCell.h"
#include "QuadTree.h"

class GameState {
public:
    std::vector<MapCell> cells;
    std::list<Agent> agents;
    QuadTree* quadTree = nullptr;
};



