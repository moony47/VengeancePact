#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

#include "QuadTree.h"
#include "GameStateManager.h"

//struct Node
//{
//	Node* pred;
//	sf::Vector2i pos;
//
//	float g, h;
//
//	Node(const sf::Vector2i& _pos, const float _h)
//		: pos(_pos), pred(nullptr), g(FLT_MAX), h(_h) {}
//
//	bool operator==(const Node& rhs) const
//	{
//		return pos == rhs.pos;
//	}
//
//	bool operator==(const sf::Vector2i& rhs) const
//	{
//		return pos == rhs;
//	}
//};

class MovementManager
{
public:
	MovementManager();
	~MovementManager();

	std::vector<sf::Vector2f> AStarPathFind(const sf::Vector2f, const sf::Vector2f, const GameStateManager& gameStateManager);
private:
	std::vector<sf::Vector2f> retracePath(QuadTreeNav&, const sf::Vector2f source, const sf::Vector2f target);
	float euclideanDistance(const sf::Vector2f, const sf::Vector2f) const;
	void clearNodes(std::vector<QuadTreeNav*>);
};