#pragma once
#include <cmath>
#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"


class GameStateManager {
public:
    GameStateManager(unsigned int numCells);

    void initialiseQuadTree(unsigned int battlefieldSize, unsigned int& i);
    void initializeBattlefieldVector(unsigned int numCells);

    GameState& getState() { return gameState; }

    void moveClouds(float dt, float scale);
private:
    void generateQuadTree(QuadTree* root, unsigned int& i);
    MapCell generateCell(int x, int y);

    void spawnRandomClouds(unsigned int num);

    BattlefieldMap battlefieldMap;
    GameState gameState;
};
  