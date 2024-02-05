#include "Scene.h"

#define MAX_TILE_DEPTH 3
#define TILE_SIZE 500

Scene::Scene() {}

void Scene::UpdateGameScene(sf::View& view, GameState& gameState) {
	sf::FloatRect viewbounds(view.getCenter() - (view.getSize() / 2.f), view.getSize());

	gameScene.clear();
	findViewportIterators(view, gameState.quadTree, viewbounds);
}

void Scene::findViewportIterators(sf::View& view, QuadTree* root, sf::FloatRect& viewbounds) {
	sf::Vector2f isometricPosition = GridGenerator::cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE), 250.f);

	int sizeX = root->quadRect.getSize().x;
	int sizeY = (root->quadRect.getSize().y / 2 + (TILE_SIZE / 2) * MAX_TILE_DEPTH);

	sf::FloatRect isometricNodeRect(isometricPosition.x - (sizeX - TILE_SIZE) / 2, isometricPosition.y - ((TILE_SIZE / 2) * MAX_TILE_DEPTH), sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect))
		return;

	if (typeid(*root) == typeid(QuadTreeLeaf)) {
		gameScene.insert(((QuadTreeLeaf*)root)->cellIter);
		gameSceneAgents.insert(gameSceneAgents.end(), ((QuadTreeLeaf*)root)->agentIters.begin(), ((QuadTreeLeaf*)root)->agentIters.end());
	} else {
		for (QuadTree* child : ((QuadTree*)root)->children)
			findViewportIterators(view, child, viewbounds);
	}
}