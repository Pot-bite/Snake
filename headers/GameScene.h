#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Button.h"

class GameScene : public Scene {
public:
    GameScene();  // Constructor

    Object m_object;
    Button button1;

    // Move operations
    GameScene(GameScene&&) = default;
    GameScene& operator=(GameScene&&) = default;

    // Delete copy operations
    GameScene(const GameScene&) = delete;
    GameScene& operator=(const GameScene&) = delete;

    void Start(sf::RenderWindow& window) override;
    void Update(float deltaTime, sf::RenderWindow& m_window) override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

private:
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::RenderWindow* m_window;

    bool isPaused = false;
    sf::RectangleShape pauseOverlay;
    
};