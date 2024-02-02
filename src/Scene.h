#pragma once
#include <set>
#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(Camera& cam, GameState& gameState);

	std::set<std::vector<MapCell>::iterator> gameScene;
	std::vector<std::list<Agent>::iterator> gameSceneAgents;
private:
	void findViewportIterators(QuadTree* root, Camera& cam, sf::IntRect& viewbounds);
};