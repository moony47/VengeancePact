#include "Camera.h"

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "Pan and Zoom", sf::Style::Fullscreen) {
    window.setFramerateLimit(165);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

    sf::Vector2u screenSize = window.getSize();
    offsetX = -(screenSize.x / 2.0f);
    offsetY = -(screenSize.y / 2.0f);
}

bool Camera::Update(float dt) {
    sf::Event event;
    window.pollEvent(event);

    if (event.type == sf::Event::Closed) {
        return false;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        return false;
    }

    Zoom(event, dt);
    Pan(event, dt);
}

void Camera::WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY) 
{
    outScreenX = (int)((worldX - offsetX) * scale);
    outScreenY = (int)((worldY - offsetY) * scale);
}

void Camera::ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY)
{
    outWorldX = ((float)screenX / scale) + offsetX;
    outWorldY = ((float)screenY / scale) + offsetY;
}

void Camera::Pan(sf::Event& event, float dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();
    const int edgeThreshold = windowSize.y / 20;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = true;
        startPanX = mousePos.x;
        startPanY = mousePos.y;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = false;
    }

    if (mouseButtonPanning) {
        offsetX -= (mousePos.x - startPanX) / scale;
        offsetY -= (mousePos.y - startPanY) / scale;

        startPanX = mousePos.x;
        startPanY = mousePos.y;
    }
    else {
        float panSpeedX = 0.0f;
        float panSpeedY = 0.0f;

        if (mousePos.x <= edgeThreshold)
            panSpeedX = (edgeThreshold - mousePos.x) / (static_cast<float>(edgeThreshold) * scale);
        else if (mousePos.x >= static_cast<int>(windowSize.x) - edgeThreshold)
            panSpeedX = -(mousePos.x - (static_cast<int>(windowSize.x) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scale);

        if (mousePos.y <= edgeThreshold)
            panSpeedY = (edgeThreshold - mousePos.y) / (static_cast<float>(edgeThreshold) * scale);
        else if (mousePos.y >= static_cast<int>(windowSize.y) - edgeThreshold)
            panSpeedY = -(mousePos.y - (static_cast<int>(windowSize.y) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scale);

        if (panSpeedX != 0.0f || panSpeedY != 0.0f) {
            offsetX -= panSpeedX * 1000 * dt;
            offsetY -= panSpeedY * 1000 * dt;
        }
    }

    //Clamp the offset so we can't pan off to infinity and beyond
    /*if (offsetX > 12000) offsetX = 12000;
    if (offsetX < -12000) offsetX = -12000;
    if (offsetY > 10500) offsetY = 10500;
    if (offsetY < -500) offsetY = -500;*/
}

void Camera::Zoom(sf::Event& event, float dt) {
    const float maxScale = std::powf(1 + 0.1111f, 5), minScale = std::powf(1 - 0.1f, 5);

    if (event.type == sf::Event::MouseWheelScrolled) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float worldXBeforeZoom, worldYBeforeZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXBeforeZoom, worldYBeforeZoom);

        if (event.mouseWheelScroll.delta > 0) {
            scale *= 1 + 0.1111f; //Use dt?
            if (scale > maxScale)
                scale = maxScale;
        } else if (event.mouseWheelScroll.delta < 0) {
            scale *= 1 - 0.1f; //Use dt?
            if (scale < minScale)
                scale = minScale;
        }

        std::cout << scale << std::endl;

        float worldXAfterZoom, worldYAfterZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

        offsetX += worldXBeforeZoom - worldXAfterZoom;
        offsetY += worldYBeforeZoom - worldYAfterZoom;

        //Clamp the offset so we can't pan off to infinity and beyond
        /*if (offsetX > 12000) offsetX = 12000;
        if (offsetX < -12000) offsetX = -12000;
        if (offsetY > 10500) offsetY = 10500;
        if (offsetY < -500) offsetY = -500;*/
    }
}

void Camera::DrawSceneAgents(std::vector<std::list<Agent>::iterator>& gameSceneAgents) {
    for (auto iter = gameSceneAgents.begin(); iter != gameSceneAgents.end(); iter++) {
        Agent agent = **iter;
        DrawTexture(*agent.texture, agent.x, agent.y);
    }
}

void Camera::DrawScene(std::set<std::vector<MapCell>::iterator>& gameScene) {
    for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++) {
        MapCell cell = **iter;
        DrawTexture(*cell.texture, cell.x, cell.y);
        for (Scenery* obj : cell.scenery)
            DrawTexture(*obj->texture, obj->x, obj->y);
    }
}

void Camera::DrawTexture(sf::Texture& texture, float x, float y) {
    sf::Sprite sprite = sf::Sprite();

    sprite.setTexture(texture);

    int screenX, screenY;
    sf::Vector2f isometricPosition = GridGenerator::cartesianToIsometricTransform(sf::Vector2f(x, y));
    WorldToScreen(isometricPosition.x + window.getSize().x / 2, isometricPosition.y, screenX, screenY);

    sprite.setPosition(screenX - 100 * scale, screenY);
    sprite.setScale(scale, scale);

    window.draw(sprite);
}