#include "Snake.h"
#include <iostream>


Object::Object(sf::Vector2f position, float mass, float elasticity)
    : mass(mass),
    elasticity(elasticity),
    velocity({ 0, 0 }),
    snakeSprite(snakeTexture)
{
    if (!snakeTexture.loadFromFile("assets/graphics/snakehead.png")) {
        std::cerr << "Error with images";
    }
    snakeSprite.setTexture(snakeTexture, true);

    bounds = snakeSprite.getGlobalBounds();
    snakeSprite.setOrigin({ bounds.size.x / 5, bounds.size.x / 5 });  // Rotate around center

}

void Object::update(float deltaTime) {
    // Apply movement
    snakeSprite.move(velocity * deltaTime);
}
