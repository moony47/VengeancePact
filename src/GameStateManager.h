#pragma once
#include <cmath>
#include "GameState.h"
#include "BattlefieldMap.h"
#include "MapCell.h"


class GameStateManager {
public:
    GameStateManager(unsigned int numCells);

    void initialiseQuadTree(unsigned int battlefieldSize, unsigned int& i);
    void initializeBattlefieldVector(unsigned int numCells);

    GameState& getState() { return gameState; }

    void moveClouds(float dt, float scale);

    QuadTree* getQuadTreeNode(sf::Vector2f point);
private:
    void generateQuadTree(QuadTree* root, unsigned int& i);
    MapCell generateCell(int x, int y);

    void setQuadTreeNavNeighbours(QuadTree* root);

    QuadTree* getQuadTreeNode(QuadTree* root, sf::Vector2f point);

    void spawnRandomClouds(unsigned int num);

    BattlefieldMap battlefieldMap;
    GameState gameState;
};
  