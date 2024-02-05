#pragma once
#include <iostream>
#include <set>

#include "GameStateManager.h"
#include "GridGenerator.h"
#include "Weather.h"

class Camera {
public:
    Camera(sf::Vector2u screenSize);

    void DrawScene(sf::RenderWindow& window, Weather& weather, std::set<std::vector<MapCell>::iterator>& gameScene);
    void DrawSceneAgents(sf::RenderWindow& window, Weather& weather, std::vector<std::list<Agent>::iterator>& gameSceneAgents);

    sf::View view;

    void Pan(sf::RenderWindow& window, sf::Event& event, float dt);
    void Zoom(sf::RenderWindow& window, sf::Event& event, float dt);

private:
    bool mouseButtonPanning = false;
    bool edgePanning = false;

    float startPanX = 0.f;
    float startPanY = 0.f;

    void DrawTexture(sf::RenderWindow& window, Weather& weather, sf::Texture& texture, float x, float y);
    float viewScale(sf::RenderWindow& window) { return window.getSize().x / view.getSize().x; }
};