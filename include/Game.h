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

    bool isGameOver = false;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        auto isJumpKeyPressed = [] {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
            };

        auto isDuckKeyPressed = [] {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
            };

        if (!isGameOver)
        {
            if (isJumpKeyPressed())
                player.Jump();
            else if (isDuckKeyPressed())
                player.Duck();
            else
                player.Unduck();

            player.Update(deltaTime);
            world.Update(deltaTime);

            for (const auto& obstacle : world.GetObstacles())
            {
                if (player.GetBounds().findIntersection(obstacle.m_Sprite.getGlobalBounds()))
                {
                    player.Death();
                    isGameOver = true;
                    break;
                }
            }
        }

        window.clear(sf::Color::White);

        world.Draw(window);
        player.Draw(window);

        window.display();
    }
}
