
#include "GameScene.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include <iostream>
#include "Snake.h"



GameScene::GameScene()
    : m_backgroundSprite(m_backgroundTexture),
    m_object(sf::Vector2f({0,0}))
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
    
}

void GameScene::Update(float deltaTime)
{
    m_object.snakeSprite.move(m_object.velocity * deltaTime);
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
    window.draw(m_object.snakeSprite);
}

void GameScene::HandleEvent(const sf::Event& event)
{
     if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Backspace)
     {
        SceneManager::getInstance().SetActiveScene(std::make_unique<MainMenuScene>());
     }
}