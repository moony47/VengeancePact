#include "Game.h"

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "Vengeance Pact", sf::Style::Fullscreen),
    gameStateManager(mapSize* mapSize),
    camera(window.getSize()){

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
            camera.Pan(window, event, dt);
        }

        //Update Scene
        scene.UpdateGameScene(camera.view, gameStateManager.getState());

        //Rendering
        window.clear(sf::Color().Black);

        camera.DrawScene(window, scene.gameScene);
        camera.DrawSceneAgents(window, scene.gameSceneAgents);

        window.display();
    }
    window.close();
}