#pragma once
#include <SFML/Graphics.hpp>

class Object {
public:
    sf::Sprite snakeSprite;  
    sf::Texture snakeTExture;
    sf::Vector2f velocity;   
    float mass;             
    float elasticity;    

    Object(sf::Vector2f position, float mass = 1.0f, float elasticity = 0.5f);
      

    bool checkCollision(const Object& other) const {
        
        return (bool)snakeSprite.getGlobalBounds().findIntersection(other.snakeSprite.getGlobalBounds());
    }
};
