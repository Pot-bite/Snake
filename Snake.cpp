#include "Snake.h"
#include <iostream>


Object::Object(sf::Vector2f position, float mass, float elasticity)
    : mass(mass), 
    elasticity(elasticity), 
    velocity({ 0, 0 }) ,
    snakeSprite(snakeTexture)
{
    if (!snakeTexture.loadFromFile("assets/graphics/snakehead.png")) {
        std::cerr << "Error with images";
    }
    snakeSprite.setTexture(snakeTexture, true);
    snakeSprite.setPosition(position);
}

void Object::update(float deltaTime) {
    snakeSprite.move(velocity * deltaTime); 
}
