#include "Camera.h"

Camera::Camera(sf::Vector2u screenSize)
    : view(sf::Vector2f(screenSize / (unsigned)2), sf::Vector2f(screenSize)) {
}

void Camera::Pan(sf::RenderWindow& window, sf::Event& event, float dt) {
    window.setView(view);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();
    const int edgeThreshold = windowSize.y / 20;
    float scale = viewScale(window);


    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = true;
        startPanX = mousePos.x;
        startPanY = mousePos.y;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = false;
    }

    if (mouseButtonPanning) {
        view.move(-(mousePos.x - startPanX) / scale, -(mousePos.y - startPanY) / scale);

        startPanX = mousePos.x;
        startPanY = mousePos.y;
    } else {
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

        if (panSpeedX != 0.0f || panSpeedY != 0.0f)
            view.move(-panSpeedX * 1000 * dt, -panSpeedY * 1000 * dt);
    }

    //Clamp the offset so we can't pan off to infinity and beyond
    /*if (offsetX > 12000) offsetX = 12000;
    if (offsetX < -12000) offsetX = -12000;
    if (offsetY > 10500) offsetY = 10500;
    if (offsetY < -500) offsetY = -500;*/
    window.setView(window.getDefaultView());
}

void Camera::Zoom(sf::RenderWindow& window, sf::Event& event, float dt) {
    const float maxScale = std::powf(1.1111111111111f, 10), minScale = std::powf(0.9f, 10);
    float scale = viewScale(window);

    if (event.type == sf::Event::MouseWheelScrolled) {
        window.setView(view);
        if (event.mouseWheelScroll.delta > 0 && scale < maxScale) {
            view.zoom(0.9f);
            view.move(((sf::Vector2f(window.mapPixelToCoords((sf::Mouse::getPosition())) - sf::Vector2f(view.getCenter()))).x) * 0.1f,
                ((sf::Vector2f(window.mapPixelToCoords((sf::Mouse::getPosition())) - sf::Vector2f(view.getCenter()))).y) * 0.1f);
        } else if (event.mouseWheelScroll.delta < 0 && scale > minScale) {
            view.zoom(1.1111111111111f);
            view.move(((sf::Vector2f(window.mapPixelToCoords((sf::Mouse::getPosition())) - sf::Vector2f(view.getCenter()))).x) * -0.1111111111111f,
                ((sf::Vector2f(window.mapPixelToCoords((sf::Mouse::getPosition())) - sf::Vector2f(view.getCenter()))).y) * -0.1111111111111f);
        }

        //Clamp the offset so we can't pan off to infinity and beyond
        /*if (offsetX > 12000) offsetX = 12000;
        if (offsetX < -12000) offsetX = -12000;
        if (offsetY > 10500) offsetY = 10500;
        if (offsetY < -500) offsetY = -500;*/
    }
}

void Camera::DrawSceneAgents(sf::RenderWindow& window, Weather& weather, std::vector<std::list<Agent>::iterator>& gameSceneAgents) {
    window.setView(view);
    weather.cloudShaderUpdate();
    for (auto iter = gameSceneAgents.begin(); iter != gameSceneAgents.end(); iter++) {
        Agent agent = **iter;
        DrawTexture(window, weather, *agent.texture, agent.x, agent.y);
    }
}

void Camera::DrawScene(sf::RenderWindow& window, Weather& weather, std::set<std::vector<MapCell>::iterator>& gameScene) {
    window.setView(view);
    weather.cloudShaderUpdate();
    for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++) {
        MapCell cell = **iter;
        DrawTexture(window, weather, *cell.texture, cell.x, cell.y);
        for (Scenery* obj : cell.scenery)
            DrawTexture(window, weather, *obj->texture, obj->x, obj->y);
    }
}

void Camera::DrawTexture(sf::RenderWindow& window, Weather& weather, sf::Texture& texture, float x, float y) {
    sf::Sprite sprite = sf::Sprite();

    sprite.setTexture(texture);

    sf::Vector2f isometricPosition = GridGenerator::cartesianToIsometricTransform({x, y}, 250.f);
    sprite.setPosition(isometricPosition);
    sprite.setOrigin({0, 500});

    window.draw(sprite, weather.getCloudShader(texture));
}