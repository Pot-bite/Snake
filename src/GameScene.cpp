
#include "GameScene.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include <iostream>
#include "Snake.h"
#include "Button.h"
#include "MenuButton.h"
#include "Scene.h"



GameScene::GameScene()
    : m_backgroundSprite(m_backgroundTexture),
    m_object(sf::Vector2f({0,0})),
   isPaused(false),
    conButton("Continue", sf::Vector2f(500, 300), sf::Color::White),
    menuButton("Menu", sf::Vector2f(150, 100), sf::Color::White),
    exitButton("Exit", sf::Vector2f(500, 300), sf::Color::White),
    isClosed(false)
{
    if (m_backgroundTexture.loadFromFile("assets/graphics/floor.png")) {
        m_backgroundSprite.setTexture(m_backgroundTexture, true);
        m_backgroundSprite.setPosition({ 0,0 });
    }
    else {
        std::cerr << "Failed to load floor.png. Background sprite disabled." << std::endl;

    }    
    
    

}


void GameScene::Start(sf::RenderWindow& window)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = m_backgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    m_backgroundSprite.setScale({ scaleX, scaleY });
    
    sf::Vector2f snakePos = static_cast<sf::Vector2f>(windowSize);
    m_object.snakeSprite.setPosition({snakePos.x / 2, snakePos.y / 2});

    m_window = &window;

    pauseOverlay.setFillColor(sf::Color(0, 0, 0, 128));
    pauseOverlay.setPosition({ 0,0 });
    pauseOverlay.setSize(sf::Vector2f(window.getSize()));


    
    sf::Vector2f conButtonPos = static_cast<sf::Vector2f>(windowSize) / 2.0f;
    conButtonPos.y -= 300.0f;  // Move up by 100 pixels from center
    conButton.Start(window, conButtonPos);

    sf::Vector2f menuButtonPos = static_cast<sf::Vector2f>(windowSize);
    menuButtonPos.x -= menuButton.button.getSize().x;  // Subtract button width from window width
    menuButtonPos.y = 100.0f;  // Keep your desired top margin
    menuButton.Start(window, menuButtonPos);

    sf::Vector2f exitButtonPos = static_cast<sf::Vector2f>(windowSize) / 2.0f;
    exitButtonPos.y += conButtonPos.y / 4.0f;
    exitButton.Start(window, exitButtonPos);
    
}

void GameScene::Update(float deltaTime, sf::RenderWindow& m_window)
{
    if (isPaused)
        return;

    
    

        sf::Vector2f prevVelocity = m_object.velocity;

        // Handle direction changes (only modify velocity when keys are pressed)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            m_object.velocity.x = 100.0f;  // Right
            m_object.velocity.y = 0.0f;    // Cancel vertical movement
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            m_object.velocity.x = -100.0f; // Left
            m_object.velocity.y = 0.0f;     // Cancel vertical movement
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            m_object.velocity.y = -100.0f;  // Up
            m_object.velocity.x = 0.0f;     // Cancel horizontal movement
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            m_object.velocity.y = 100.0f;   // Down
            m_object.velocity.x = 0.0f;     // Cancel horizontal movement
        }

        // Only update rotation if velocity changed
        if (m_object.velocity != prevVelocity && m_object.velocity != sf::Vector2f(0, 0))
        {
            // Calculate angle in radians from velocity vector
            float angle = std::atan2(m_object.velocity.y, m_object.velocity.x);
            // Convert to degrees
            float degrees = angle * (180.0f / 3.14159265f);

            m_object.snakeSprite.setRotation(sf::degrees(degrees));
        }


        // Apply continuous movement 
        m_object.snakeSprite.move(m_object.velocity * deltaTime);



        sf::Vector2u windowSize = m_window.getSize();
        sf::Vector2f position = m_object.snakeSprite.getPosition();

        // Get sprite dimensions (if needed for precise wrapping)
        sf::FloatRect bounds = m_object.snakeSprite.getGlobalBounds();

        // Screen wrapping logic
        if (position.x > windowSize.x + (bounds.size.x / 5)) {
            position.x = 0 - bounds.size.x / 5;  // Wrap to left with half-sprite offset
        }
        else if (position.x < -bounds.size.x / 5) {
            position.x = windowSize.x + bounds.size.x / 5;  // Wrap to right
        }

        if (position.y > windowSize.y + (bounds.size.y) / 5) {
            position.y = 0 - bounds.size.y / 5;  // Wrap to top
        }
        else if (position.y < -bounds.size.y / 5) {
            position.y = windowSize.y + bounds.size.y / 5;  // Wrap to bottom
        }

        // Apply new position if wrapping occurred
        m_object.snakeSprite.setPosition(position);

        
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
    window.draw(m_object.snakeSprite);

    window.draw(menuButton.button);
    menuButton.ChangeColor(window);

    if (isPaused) {
        window.draw(pauseOverlay);

        window.draw(conButton.button);
        conButton.ChangeColor(window);

        window.draw(exitButton.button);
        exitButton.ChangeColor(window);
    }
        

}

void GameScene::HandleEvent(const sf::Event& event)
{
     if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Backspace)
     {
        SceneManager::getInstance().SetActiveScene(std::make_unique<MainMenuScene>());
     }
     else if(auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
     {
         if (mouseEvent->button == sf::Mouse::Button::Left) {
             // Convert mouse position to world coordinates
             sf::Vector2f mousePos = m_window->mapPixelToCoords(
                 { mouseEvent->position.x, mouseEvent->position.y });

             // Check if click was on the button
             if (menuButton.button.getGlobalBounds().contains(mousePos)) {
                 isPaused = true;  // pause the game
             }
         }
         
     }

     if (isPaused) {
         if (auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
             if (mouseEvent->button == sf::Mouse::Button::Left) {
                 // Convert mouse position to world coordinates
                 sf::Vector2f mousePos = m_window->mapPixelToCoords(
                     { mouseEvent->position.x, mouseEvent->position.y });

                 // Check if click was on the button
                 if (conButton.button.getGlobalBounds().contains(mousePos)) {
                     isPaused = false;  // Unpause the game
                 }

                 if (exitButton.button.getGlobalBounds().contains(mousePos)) {
                     isClosed = true;
                 }

             }
         }
     }

     
}

bool GameScene::IsClosed() const {
    return isClosed;
}
