#pragma once
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

#include "GameStateManager.h"
#include "GridGenerator.h"

class Camera {
public:
    Camera();

    bool Update(float dt);
    void DrawScene(std::set<std::vector<MapCell>::iterator>& gameScene);
    void DrawSceneAgents(std::vector<std::list<Agent>::iterator>& gameSceneAgents);

    void WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY);
    void ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY);

    sf::RenderWindow window; 
    
    float offsetX = 0.f;
    float offsetY = 0.f;

    float scale = 1.f;
private:
    sf::View view;

    bool mouseButtonPanning = false;
    bool edgePanning = false;

    float startPanX = 0.f;
    float startPanY = 0.f;

    void Pan(sf::Event& event, float dt);
    void Zoom(sf::Event& event, float dt);

    void DrawTexture(sf::Texture& texture, float x, float y);
};