#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:

    Button(); // Default constructor (declaration)
    Button(std::string t, sf::Vector2f size, sf::Color bgcolor); // Parameterized constructor
    

    void Start(sf::RenderWindow& window, sf::Vector2f pos);


    void ChangeColor(sf::RenderWindow& window);


    bool MouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return button.getGlobalBounds().contains(mousePos);
    }

    sf::RectangleShape button;
    sf::Text text;

private:
    sf::Font font; // Font should be loaded only once
};