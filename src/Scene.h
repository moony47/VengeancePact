#pragma once
#include <set>
#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(sf::View& view, GameState& gameState);

	std::set<std::vector<MapCell>::iterator> gameScene;
	std::vector<std::list<Agent>::iterator> gameSceneAgents;
private:
	void findViewportIterators(sf::View& view, QuadTree* root, sf::FloatRect& viewbounds);
};