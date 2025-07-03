#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Define some constants
    const float        gameWidth = 800;
    const float        gameHeight = 800;
    const float        ballRadius = gameHeight / 4.f;

    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned int>(gameWidth), static_cast<unsigned int>(gameHeight) }), "SFML window works!", sf::Style::Default, sf::State::Windowed, contextSettings);

    // Make it the active window for OpenGL calls
   //  if (!window.setActive())
   //  {
   //      std::cerr << "Failed to set the window as active" << std::endl;
   //      return EXIT_FAILURE;
   //  }

    sf::CircleShape ball;
    ball.setRadius(ballRadius - 3);
    ball.setOutlineThickness(2);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::Green);
    //ball.setOrigin({ballRadius / 2.f, ballRadius / 2.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Window closed or escape key pressed: exit
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            {
                window.close();
                break;
            }

        }

        window.clear(sf::Color(50, 20, 50));
        ball.setPosition({ (gameWidth / 2.f) - ballRadius, (gameHeight / 2.f) - ballRadius });
        window.draw(ball);
        window.display();
    }

    return EXIT_SUCCESS; //0;
}
