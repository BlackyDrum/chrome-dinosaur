#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "World.h"
#include "Globals.h"

inline sf::FloatRect InflateRect(const sf::FloatRect& rect, float dx, float dy)
{
    return sf::FloatRect(sf::Vector2f(rect.position.x + dx, rect.position.y + dy), sf::Vector2f(rect.size.x - 2 * dx, rect.size.y - 2 * dy));
}

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

            float shrinkAmount = 10.0f;
            sf::FloatRect playerBounds = InflateRect(player.GetBounds(), shrinkAmount, shrinkAmount);

            for (const auto& obstacle : world.GetObstacles())
            {
                sf::FloatRect obstacleBounds = InflateRect(obstacle.m_Sprite.getGlobalBounds(), shrinkAmount, shrinkAmount);

                if (playerBounds.findIntersection(obstacleBounds))
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
