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

    QuadTree* getQuadTreeNode(const sf::Vector2f point) const;
private:
    void generateQuadTree(QuadTree* root, unsigned int& i);
    MapCell generateCell(int x, int y);

    void setQuadTreeNavNeighbours(QuadTree* root);

    QuadTree* getQuadTreeNode(QuadTree* root, const sf::Vector2f point) const;

    void spawnRandomClouds(unsigned int num);

    BattlefieldMap battlefieldMap;
    GameState gameState;
};
  