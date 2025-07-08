
#include "GameScene.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include <iostream>


GameScene::GameScene()
    : m_backgroundSprite(m_backgroundTexture)
{

}



void GameScene::Start(sf::RenderWindow& window)
{
    if (m_backgroundTexture.loadFromFile("assets/graphics/raw.png")) {
        m_backgroundSprite.setTexture(m_backgroundTexture);
    }
    
}

void GameScene::Update(float deltaTime)
{
    
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
}

void GameScene::HandleEvent(const sf::Event& event)
{
     if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A)
     {
        SceneManager::getInstance().SetActiveScene(std::make_unique<MainMenuScene>());
     }
}