#pragma once
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

#include "GameStateManager.h"
#include "GridGenerator.h"

class Camera {
public:
    Camera(sf::Vector2u screenSize);

    //bool Update(sf::RenderWindow& window, float dt);
    void DrawScene(sf::RenderWindow& window, std::set<std::vector<MapCell>::iterator>& gameScene);
    void DrawSceneAgents(sf::RenderWindow& window, std::vector<std::list<Agent>::iterator>& gameSceneAgents);

    //void WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY);
    //void ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY);

    sf::View view;

    //float offsetX = 0.f;
    //float offsetY = 0.f;

    //float scale = 1.f;

    void Pan(sf::RenderWindow& window, sf::Event& event, float dt);
    void Zoom(sf::RenderWindow& window, sf::Event& event, float dt);
private:

    bool mouseButtonPanning = false;
    bool edgePanning = false;

    float startPanX = 0.f;
    float startPanY = 0.f;

    sf::Shader spotlightShader;

    void DrawTexture(sf::RenderWindow& window, sf::Texture& texture, float x, float y);
};