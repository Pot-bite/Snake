#include "Button.h"
#include <iostream>

// Default constructor
Button::Button()
    : text(font)  // Initialize text with font
{
    // Load font (replace with your actual font path)
    if (!font.openFromFile("assets/fonts/KOMIKAX_.ttf")) {
        std::cerr << "Error: Failed to load font!\n";
    }

    // Default button properties
    button.setSize(sf::Vector2f(200.f, 200.f));
    button.setFillColor(sf::Color::White);

    // Default text properties
    text.setString("Button");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(50);
}

// Parameterized constructor
Button::Button(std::string t, sf::Vector2f size, sf::Color bgcolor)
    : text(font)  // Initialize text with font
{
    // Load font (same as default constructor)
    if (!font.openFromFile("assets/fonts/KOMIKAX_.ttf")) {
        std::cerr << "Error: Failed to load font!\n";
    }

    // Set button properties from parameters
    button.setSize(size);
    button.setFillColor(bgcolor);

    // Set text properties
    text.setString(t);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(50);
}

void Button::Start(sf::RenderWindow& window, sf::Vector2f pos)
{
    // Set origin to center of button
    button.setOrigin({ button.getSize().x / 2, button.getSize().y / 2 });
    button.setPosition(pos);

    // Center text relative to button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({ textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f });
    text.setPosition(pos);
}

void Button::ChangeColor(sf::RenderWindow& window) {

    window.draw(text);

    if (MouseOver(window)) {
        button.setFillColor(sf::Color::Red);
    }
    else
    {
        button.setFillColor(sf::Color::White);
    }

}
