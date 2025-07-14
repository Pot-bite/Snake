#pragma once
#include <SFML/Graphics.hpp>

class Object {
public:
    sf::Sprite snakeSprite;
    sf::Texture snakeTexture;  // Fixed typo (TExture ? Texture)
    sf::Vector2f velocity;
    float mass;
    float elasticity;
    sf::FloatRect bounds;

    // Constructor with default parameters
    Object(sf::Vector2f position, float mass = 1.0f, float elasticity = 0.5f);

    // Update position based on velocity
    void update(float deltaTime);

    // Check collision between two objects
    bool checkCollision(const Object& other) const {
        const sf::FloatRect bounds1 = snakeSprite.getGlobalBounds();
        const sf::FloatRect bounds2 = other.snakeSprite.getGlobalBounds();

        return (bounds1.size.x < bounds2.size.x + bounds2.size.x) &&  // Right edge of bounds1 > Left edge of bounds2
            (bounds1.size.x + bounds1.size.x > bounds2.size.x) &&  // Left edge of bounds1 < Right edge of bounds2
            (bounds1.size.y < bounds2.size.y + bounds2.size.y) && // Bottom edge of bounds1 > Top edge of bounds2
            (bounds1.size.y + bounds1.size.y > bounds2.size.y);    // Top edge of bounds1 < Bottom edge of bounds2
    }
};