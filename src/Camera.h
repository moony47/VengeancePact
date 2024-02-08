#pragma once
#include <iostream>
#include <set>

#include "GameStateManager.h"
#include "GridGenerator.h"
#include "Weather.h"

#include "MovementManager.h"

class Camera {
public:
    Camera(sf::Vector2u screenSize);

    void DrawScene(sf::RenderWindow& window, Weather* weather, std::set<std::vector<MapCell>::iterator>& gameScene);
    void DrawSceneAgents(sf::RenderWindow& window, Weather* weather, std::vector<std::list<Agent>::iterator>& gameSceneAgents);

    sf::View view;

    void MousePan(sf::RenderWindow& window, sf::Event& event);
    void EdgePan(sf::RenderWindow& window, sf::Event& event, float dt);
    void Zoom(sf::RenderWindow& window, sf::Event& event, float dt);

    void SelectCell(sf::RenderWindow& window, sf::Event& event, GameStateManager& gameStateManager);
private:
    bool mouseButtonPanning = false;
    bool edgePanning = false;

    float startPanX = 0.f;
    float startPanY = 0.f;

    sf::Texture select;
    std::vector<sf::Vector2f> path;

    void DrawTexture(sf::RenderWindow& window, Weather* weather, sf::Texture& texture, float x, float y);
    float viewScale(sf::RenderWindow& window) { return window.getSize().x / view.getSize().x; }
};