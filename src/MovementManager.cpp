#include "MovementManager.h"

MovementManager::MovementManager() {
}

MovementManager::~MovementManager() {

}

void MovementManager::clearNodes(std::vector<QuadTreeNav*> toClear) {
	for (QuadTreeNav* node : toClear) {
		node->g = FLT_MAX;
		node->h = 0;
		node->prev = nullptr;
		node->visited = false;
	}
}

std::vector<sf::Vector2f> MovementManager::AStarPathFind(sf::Vector2f source, sf::Vector2f target, GameStateManager& gameStateManager) {
	QuadTreeNav* sourceNode = (QuadTreeNav*)gameStateManager.getQuadTreeNode(source);
	QuadTreeNav* targetNode = (QuadTreeNav*)gameStateManager.getQuadTreeNode(target);

	if (sourceNode == nullptr || targetNode == nullptr)
		return std::vector<sf::Vector2f>();

	sourceNode->g = 0;
	sourceNode->visited = true;

	std::vector<QuadTreeNav*> openSet = { sourceNode };
	std::vector<QuadTreeNav*> closedSet;

	while (!openSet.empty())
	{
		int current = 0;
		for (int i = 1; i < openSet.size(); i++)
			if (openSet[current]->g + openSet[current]->h > openSet[i]->g + openSet[i]->h)
				current = i;

		QuadTreeNav* currentNode = openSet[current];

		if (currentNode->quadRect.contains(target)) {
			std::vector<sf::Vector2f> path = retracePath(*currentNode);
			clearNodes(openSet);
			clearNodes(closedSet);
			return path;
		}

		openSet.erase(std::next(openSet.begin(), current));
		closedSet.push_back(currentNode);

		for (QuadTreeNav* neigh : currentNode->neighbours)
		{
			if (neigh == nullptr)
				continue;

			if (neigh->walkability == 0)
				continue;
			if (!neigh->visited)
				neigh->initialiseNavNode(euclideanDistance(neigh->quadRect.getPosition(), targetNode->quadRect.getPosition()));

			float temp_g = currentNode->g + euclideanDistance(currentNode->quadRect.getPosition(), neigh->quadRect.getPosition()) / neigh->walkability;

			if (temp_g < neigh->g)
			{
				neigh->prev = currentNode;
				neigh->g = temp_g;

				if (std::find_if(openSet.begin(), openSet.end(), [n = neigh] (QuadTreeNav* c) { return c == n; }) == openSet.end())
					openSet.push_back(neigh);
			}
		}
	}

	clearNodes(openSet);
	clearNodes(closedSet);
	return std::vector<sf::Vector2f>();
}

std::vector<sf::Vector2f> MovementManager::retracePath(QuadTreeNav& start) {
	std::vector<sf::Vector2f> path;
	path.push_back(start.quadRect.getPosition());

	QuadTreeNav* current = &start;
	while (current->prev != nullptr) {
		path.push_back(current->prev->quadRect.getPosition());
		current = current->prev;
	}

	return path;
}

float MovementManager::euclideanDistance(const sf::Vector2f& v, const sf::Vector2f& u) const {
	return std::sqrtf((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y));
}