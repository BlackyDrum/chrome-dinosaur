#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

const uint32_t SCREEN_WIDTH = 1000;
const uint32_t SCREEN_HEIGHT = 300;

void Run()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "T-Rex Chrome Dinosaur Game!", sf::Style::Close);
	window.setFramerateLimit(60);

    Player player;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                player.Jump();
        }

        player.Update(deltaTime);

        window.clear();

        player.Draw(window);

        window.display();
    }
}
