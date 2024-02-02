#include "Scene.h"

#define MAX_TILE_DEPTH 5
#define TILE_SIZE 200

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState) {
	sf::IntRect viewbounds(0, 0, cam.window.getSize().x, cam.window.getSize().y);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, viewbounds);
}

void Scene::findViewportIterators(QuadTree* root, Camera& cam, sf::IntRect& viewbounds) {

	int screenX, screenY;
	sf::Vector2f isometricPosition = GridGenerator::cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y, screenX, screenY);

	int sizeX = root->quadRect.getSize().x * cam.scale;
	int sizeY = (root->quadRect.getSize().y / 2 + (TILE_SIZE / 2) * MAX_TILE_DEPTH) * cam.scale;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect))
		return;

	if (typeid(*root) == typeid(QuadTreeLeaf)) {
		gameScene.insert(((QuadTreeLeaf*)root)->cellIter);
		gameSceneAgents.insert(gameSceneAgents.end(), ((QuadTreeLeaf*)root)->agentIters.begin(), ((QuadTreeLeaf*)root)->agentIters.end());
	} else {
		for (QuadTree* child : ((QuadTree*)root)->children)
			findViewportIterators(child, cam, viewbounds);
	}
}