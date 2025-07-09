#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "MainMenuScene.h"
#include <iostream>


int main()
{

    // Create window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Snake Game");
    window.setFramerateLimit(60);

    

    // Set initial scene
    SceneManager::getInstance().SetWindow(&window);


    try {
        SceneManager::getInstance().SetActiveScene(std::make_unique<MainMenuScene>());
    }
    catch (const std::exception& e) {
        std::cerr << "Scene creation failed: " << e.what() << std::endl;
    }


    // Main game loop
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            // Window closed or escape key pressed: exit
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            {
                window.close();
                break;
            }

            

            SceneManager::getInstance().HandleEvent(*event);           
        }

        // Update current scene
        SceneManager::getInstance().Update(deltaTime);
            
        // Render
        window.clear();
        SceneManager::getInstance().Render(window);
        window.display();
    }

    return 0;
}