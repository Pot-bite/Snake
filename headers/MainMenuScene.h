#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class MainMenuScene : public Scene {
public:
    
    sf::Sprite m_backgroundSprite;
    sf::Texture m_backgroundTexture;
    sf::Font m_font;
    sf::Text m_text;
    sf::Clock m_blinkClock;
    bool m_isTextVisible;
    float m_blinkInterval;
    

    MainMenuScene();
    
    // Move semantics
    MainMenuScene(MainMenuScene&&) = default;
    MainMenuScene& operator=(MainMenuScene&&) = default;

    // Delete copy semantics
    MainMenuScene(const MainMenuScene&) = delete;
    MainMenuScene& operator=(const MainMenuScene&) = delete;

    void Start(sf::RenderWindow& window) override;
    void Update(float deltaTime, sf::RenderWindow& m_window) override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

    
};