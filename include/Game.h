#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "World.h"
#include "Globals.h"



void Run()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "T-Rex Chrome Dinosaur Game!", sf::Style::Close);
	window.setFramerateLimit(FRAME_RATE);

    Player player;
    World world;

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
		world.Update(deltaTime);

        window.clear();

        world.Draw(window);
        player.Draw(window);

        window.display();
    }
}
