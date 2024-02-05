#pragma once
#include "Camera.h"
#include "Scene.h"

class Game
{
public:
	Game();
	~Game();

private:
	const unsigned int mapSize = 32;

	sf::RenderWindow window;
	sf::Clock clock;

	GameStateManager gameStateManager;
	Camera camera;
	Scene scene;

	void Run();
};