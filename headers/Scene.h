#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void Start(sf::RenderWindow& window) = 0;
    virtual void Update(float deltaTime, sf::RenderWindow& m_window) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual void HandleEvent(const sf::Event& event) = 0;
};