#include "MainMenuScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>



MainMenuScene::MainMenuScene() 
    : m_text(m_font), 
   m_backgroundSprite(m_backgroundTexture),
  m_isTextVisible(true), 
 m_blinkInterval(0.45f)
{
    // Only initialize sprite if texture loads
    if (m_backgroundTexture.loadFromFile("assets/graphics/start-image.png")) {
        m_backgroundSprite.setTexture(m_backgroundTexture, true);
        m_backgroundSprite.setPosition({ 0, 0 });
    }
    else {
        std::cerr << "Failed to load start-image.png. Background sprite disabled." << std::endl;
       
    }

    // Load font
    if (m_font.openFromFile("assets/fonts/KOMIKAX_.ttf")) {
        m_text.setFont(m_font);
    }
    else {
        std::cerr << "Failed to load KOMIKAX_.ttf. Using default font." << std::endl;
    }
    m_text.setString("Press SPACE to start");
    m_text.setCharacterSize(60);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition({ 800, 300 });
}



void MainMenuScene::Start(sf::RenderWindow& window)
{
    
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = m_backgroundTexture.getSize();
  
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    m_backgroundSprite.setScale({ scaleX, scaleY });
 
}


void MainMenuScene::Update(float deltaTime, sf::RenderWindow& m_window)
{
    float pi = 3.14159f; // to convert into radians

    // Smooth fade instead of hard blink
    float blinkProgress = fmod(m_blinkClock.getElapsedTime().asSeconds(), m_blinkInterval * 2);
    float alpha = 255 * (0.5f + 0.5f * sin(blinkProgress * pi / m_blinkInterval));
    m_text.setFillColor(sf::Color(255, 255, 255, static_cast<float>(alpha)));
}

void MainMenuScene::Render(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);  
    window.draw(m_text);
}


void MainMenuScene::HandleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
    {
        SceneManager::getInstance().SetActiveScene(std::make_unique<GameScene>());
    }
}

bool MainMenuScene::IsClosed() const {
    return false;  
}