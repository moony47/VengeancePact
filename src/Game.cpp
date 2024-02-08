#include "Game.h"

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Vengeance Pact", sf::Style::Fullscreen),
    gameStateManager(mapSize* mapSize),
    camera(window.getSize()) {

    window.setFramerateLimit(165);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

    Run();
}

Game::~Game() {

}

void Game::Run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            //Update Camera
            camera.Zoom(window, event, dt);
            camera.MousePan(window, event);
            camera.SelectCell(window, event, gameStateManager);
        }
        camera.EdgePan(window, event, dt);

        //Move Clouds
        gameStateManager.moveClouds(dt, window.getSize().x / camera.view.getSize().x);

        //Update Scene
        scene.UpdateGameScene(camera.view, gameStateManager.getState());

        //Rendering
        window.clear(sf::Color().Black);

        camera.DrawScene(window, &gameStateManager.getState().weather, scene.gameScene);
        camera.DrawSceneAgents(window, &gameStateManager.getState().weather, scene.gameSceneAgents);

        window.display();
    }
    window.close();
}