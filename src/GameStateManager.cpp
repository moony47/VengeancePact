#include "GameStateManager.h"

#define CELLSIZE 500

GameStateManager::GameStateManager(unsigned int numCells) {
    initializeBattlefieldVector(numCells);

    gameState.weather.initCloudShader();
    spawnRandomClouds(15);
}


void GameStateManager::spawnRandomClouds(unsigned int num) {
    if (num > 20) num = 20;
    for (unsigned int i = 0; i < num; i++) {
        sf::Vector2f pos(-6000 + rand() % 12000, -2000 + rand() % 8000);
        float size = (30 + rand() % 20) / 100.f;

        gameState.weather.setCloud(
            i, pos,
            size * sf::Vector2f((rand() % 2 ? 1 : -1) * (700 + rand() % 400), (rand() % 2 ? 1 : -1) * (300 + rand() % 400)),
            size
        );
    }
}

void GameStateManager::moveClouds(float dt, float scale) {
    for (int i = 0; i < 20; i++)
        gameState.weather.moveCloud(i, sf::Vector2f(20 * dt, 40 * dt));
    gameState.weather.scaleClouds(scale);
}

void GameStateManager::initialiseQuadTree(unsigned int battlefieldSize, unsigned int& i) {
    gameState.quadTree = new QuadTree(sf::FloatRect(0, 0, battlefieldSize, battlefieldSize), 0);
    generateQuadTree((QuadTree*)gameState.quadTree, i);
}

void GameStateManager::generateQuadTree(QuadTree* root, unsigned int& i) {
    float size = root->quadRect.getSize().x / 2.f;

    if (size > CELLSIZE) {
        //Empty quadtree nodes for early pruning

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {
            int x = root->quadRect.getPosition().x + size * (k % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(k > 1));

            children[k] = new QuadTree(
                sf::FloatRect(x, y, size, size), 
                root->depth + 1
            );

            generateQuadTree((QuadTree*)children[k], i);
        }

        root->children = children;
    }
    else if (size == CELLSIZE) {
        //Cell quadtree nodes - this level contains iterators for the map cells at their positions

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {
            int x = root->quadRect.getPosition().x + size * (k % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(k > 1));

            gameState.cells[i] = generateCell(x / CELLSIZE, y / CELLSIZE);

            if (rand() % 100 < 10)
                gameState.cells[i].scenery.push_back(new Scenery(x / CELLSIZE + (rand() % 199 + 1) / 200.f, y / CELLSIZE + (rand() % 199 + 1) / 200.f));

            std::vector<MapCell>::iterator iter = gameState.cells.begin() + (i++);

            children[k] = new QuadTreeCell(
                sf::FloatRect(x, y, size, size),
                root->depth + 1,
                iter
            );

            if (rand() % 100 < 1) {
                gameState.agents.push_back(Agent(x / CELLSIZE + (rand() % 199 + 1) / 200.f, y / CELLSIZE + (rand() % 199 + 1) / 200.f));
                ((QuadTreeCell*)children[k])->agentIters.push_back(std::prev(gameState.agents.end()));
            }

            generateQuadTree((QuadTree*)children[k], i);
        }

        root->children = children;
    } else if (size > 50) {
        //Empty quadtree nodes for early pruning

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {
            int x = root->quadRect.getPosition().x + size * (k % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(k > 1));

            children[k] = new QuadTree(
                sf::FloatRect(x, y, size, size),
                root->depth + 1
            );

            generateQuadTree((QuadTree*)children[k], i);
        }

        root->children = children;
    } else {
        //Nav quadtree nodes - this level is for agent navigation 

        std::array<QuadTree*, 4> children;

        for (int k = 0; k < 4; k++) {
            int x = root->quadRect.getPosition().x + size * (k % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(k > 1));

            children[k] = new QuadTreeNav(
                sf::FloatRect(x, y, size, size),
                root->depth + 1,
                1.f
            );
        }

        root->children = children;
    }
}

void GameStateManager::setQuadTreeNavNeighbours(QuadTree* root) {
    if (typeid(*root) == typeid(QuadTreeNav)) {
        ((QuadTreeNav*)root)->setNeighbours({
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left + root->quadRect.width + 1, root->quadRect.top)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left, root->quadRect.top + root->quadRect.height + 1)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left - 1, root->quadRect.top)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left, root->quadRect.top - 1)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left - 1, root->quadRect.top - 1)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left - 1, root->quadRect.top + root->quadRect.height + 1)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left + root->quadRect.width + 1, root->quadRect.top - 1)),
            (QuadTreeNav*)getQuadTreeNode(sf::Vector2f(root->quadRect.left + root->quadRect.width + 1, root->quadRect.top + root->quadRect.height + 1))
        });
    } else {
        setQuadTreeNavNeighbours(root->children[0]);
        setQuadTreeNavNeighbours(root->children[1]);
        setQuadTreeNavNeighbours(root->children[2]);
        setQuadTreeNavNeighbours(root->children[3]);
    }
}

QuadTree* GameStateManager::getQuadTreeNode(const sf::Vector2f point) const {
    return getQuadTreeNode(gameState.quadTree, point);
}

QuadTree* GameStateManager::getQuadTreeNode(QuadTree* root, const sf::Vector2f point) const {
    if (root->children[0] == nullptr)
        return root;

    for (int k = 0; k < 4; k++)
        if (root->children[k]->quadRect.contains(point))
            return getQuadTreeNode(root->children[k], point);

    return nullptr;
}

MapCell GameStateManager::generateCell(int x, int y) {
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

void GameStateManager::initializeBattlefieldVector(unsigned int numCells) {
    srand(time(NULL));

    battlefieldMap.initMap(static_cast<unsigned int>(static_cast<int>(std::floor(std::sqrt(numCells)))));

    gameState.cells.clear();
    gameState.cells.resize(numCells); 
    gameState.agents.clear();

    unsigned int i = 0;
    initialiseQuadTree(static_cast<int>(std::floor(std::sqrt(numCells))) * CELLSIZE, i);
    setQuadTreeNavNeighbours(gameState.quadTree);
}

