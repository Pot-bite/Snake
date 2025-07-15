#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class MenuButton : public Button
{
public:

    MenuButton(); // Default constructor (declaration)
    MenuButton(std::string t, sf::Vector2f size, sf::Color bgcolor); // Parameterized constructor


    void Start(sf::RenderWindow& window, sf::Vector2f pos) override;


    void ChangeColor(sf::RenderWindow& window) override;


    bool MouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return button.getGlobalBounds().contains(mousePos);
    }

    sf::RectangleShape button;
    sf::Text text;

private:
    sf::Font font; // Font should be loaded only once
};