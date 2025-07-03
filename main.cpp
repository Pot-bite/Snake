#include <SFML/Graphics.hpp>
#include <iostream>



int main()
{
    // Create main window
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML Game");

    // text character size
    const short characterSize = 50;

    sf::Clock blinkClock;
    float blinkInterval = 0.45f; // Blink time
    bool isTextVisible = true;

    // Load texture
    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("D:/Downloads/snake/Timber/assets/graphics/start-image.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite backGroundSprite(backGroundTexture);

    // Get sizes as Vector2u (unsigned)
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backGroundTexture.getSize();

    // Calculate scale factors
    sf::Vector2f scaleFactors(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    backGroundSprite.setScale(scaleFactors);

    sf::Font font;
    font.openFromFile("D:/Downloads/snake/Timber/assets/fonts/KOMIKAX_.ttf");
    if (!font.openFromFile("D:/Downloads/snake/Timber/assets/fonts/KOMIKAX_.ttf"))
        throw std::runtime_error("Error with font");

    sf::Text text(font);
    text.setString("Press space button");
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(700, 950));

   
   
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


        // Blink logic
        if (blinkClock.getElapsedTime().asSeconds() >= blinkInterval)
        {
            isTextVisible = !isTextVisible;
            blinkClock.restart();

            if (isTextVisible)
                text.setFillColor(sf::Color::White);
            else
                text.setFillColor(sf::Color(255, 255, 255, 128));
        }



           

        window.clear();
        window.draw(backGroundSprite);
        window.draw(text);
        window.display();


    }


    return EXIT_SUCCESS;
}