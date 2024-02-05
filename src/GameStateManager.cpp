#include "GameStateManager.h"

#define CELLSIZE 500

GameStateManager::GameStateManager(unsigned int numCells) {
    initializeBattlefieldVector(numCells);
}

void GameStateManager::initialiseQuadTree(unsigned int battlefieldSize, unsigned int& i) {
    state.quadTree = new QuadTree(sf::IntRect(0, 0, battlefieldSize, battlefieldSize), 0);
    generateQuadTree((QuadTree*)state.quadTree, i);
}

void GameStateManager::generateQuadTree(QuadTree* root, unsigned int& i) {
    float size = root->quadRect.getSize().x / 2;
    if (size > CELLSIZE) {

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {

            children[k] = new QuadTree(
                sf::IntRect(
                    root->quadRect.getPosition().x + size * (k % 2),
                    root->quadRect.getPosition().y + size * ((int)(k > 1)),
                    size, size
                ), 
                root->depth + 1
            );

            generateQuadTree((QuadTree*)children[k], i);
        }

        root->children = children;
    } else {

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {
            int x = root->quadRect.getPosition().x + size * (k % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(k > 1)); 

            state.cells[i] = generateCell(x / CELLSIZE, y / CELLSIZE);

            if (rand() % 100 < 10)
                state.cells[i].scenery.push_back(new Scenery(x / CELLSIZE + (rand() % 199 + 1) / 200.f, y / CELLSIZE + (rand() % 199 + 1) / 200.f));
            
            std::vector<MapCell>::iterator iter = state.cells.begin() + (i++);

            children[k] = new QuadTreeLeaf(
                sf::IntRect(x, y, size, size), 
                root->depth + 1,
                iter
            );

            if (rand() % 100 < 1) {
                state.agents.push_back(Agent(x / CELLSIZE + (rand() % 199 + 1) / 200.f, y / CELLSIZE + (rand() % 199 + 1) / 200.f));
                ((QuadTreeLeaf*)children[k])->agentIters.push_back(std::prev(state.agents.end()));
            }
        }

        root->children = children;
    }
}

MapCell GameStateManager::generateCell(int x, int y)
{
    TerrainTile newTerr;
    newTerr.depth = battlefieldMap.getHeightAtPosition({x, y});
    newTerr.facing = 0;
    newTerr.terrain = "default";

    MapCell newCell;
    newCell.x = x;
    newCell.y = y;
    newCell.terrain = newTerr;
    newCell.texture = battlefieldMap.getTextureAtPosition({x, y});

    return newCell;
}

void GameStateManager::initializeBattlefieldVector(unsigned int numCells) 
{
    srand(time(NULL));

    battlefieldMap.initMap(static_cast<unsigned int>(static_cast<int>(std::floor(std::sqrt(numCells)))));

    state.cells.clear();
    state.cells.resize(numCells); 
    state.agents.clear();

    unsigned int i = 0;
    initialiseQuadTree(static_cast<int>(std::floor(std::sqrt(numCells))) * CELLSIZE, i);
}

