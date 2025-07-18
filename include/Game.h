#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "World.h"
#include "UI.h"
#include "SoundManager.h"
#include "Globals.h"

inline sf::FloatRect InflateRect(const sf::FloatRect& rect, float dx, float dy)
{
    return sf::FloatRect(sf::Vector2f(rect.position.x + dx, rect.position.y + dy), sf::Vector2f(rect.size.x - 2 * dx, rect.size.y - 2 * dy));
}

void Run()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Chrome Dinosaur Game");

    Player player;
    World world;
    UI ui;
    SoundManager soundManager;

    bool isGameOver = false;
    bool checkpointPlayed = false;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (isGameOver && event->is<sf::Event::MouseButtonPressed>())
            {
                const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f clickPos = window.mapPixelToCoords(mouseEvent->position);
                    if (ui.GetRestartButtonBounds().contains(clickPos))
                    {
                        player.Reset();
                        world.Reset();
                        ui.Reset();

                        isGameOver = false;
                    }
                }
            }
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
            {
                if (player.Jump())
                    soundManager.PlayJumpSound();
            }
            else if (isDuckKeyPressed())
            {
                player.Duck();
            }
            else
            {
                player.Unduck();
            }

            player.Update(deltaTime);
            world.Update(deltaTime);
            ui.Update(deltaTime);

            // Detect collision with obstacles
            float shrinkAmount = 10.0f;
            sf::FloatRect playerBounds = InflateRect(player.GetBounds(), shrinkAmount, shrinkAmount);

            for (const auto& obstacle : world.GetObstacles())
            {
                sf::FloatRect obstacleBounds = InflateRect(obstacle.m_Sprite.getGlobalBounds(), shrinkAmount, shrinkAmount);

                if (playerBounds.findIntersection(obstacleBounds))
                {
                    player.Death();
                    ui.SetGameOver(true);
                    soundManager.PlayDieSound();
                    isGameOver = true;

                    break;
                }
            }

            uint32_t score = ui.GetScore();
            if (score % 100 == 0 && score > 0 && !checkpointPlayed)
            {
                soundManager.PlayScoreSound();
                checkpointPlayed = true;
            }
            else if (score % 100 != 0)
            {
                checkpointPlayed = false;
            }
        }

        window.clear(sf::Color::White);

        world.Draw(window);
        player.Draw(window);
        ui.Draw(window);

        window.display();
    }
}
