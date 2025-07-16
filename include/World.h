#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Globals.h"

class World
{
public:
    World();

    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetBounds() const;

private:
    sf::Texture m_Texture;
    sf::Sprite m_Ground1;
    sf::Sprite m_Ground2;
    float m_GroundY;
    float m_ScrollSpeed = 200.0f;

    struct Obstacle
    {
        Obstacle(sf::Texture& texture) : sprite(texture) {}
        sf::Sprite sprite;
    };

    std::vector<sf::IntRect> m_CactusRects;

	std::vector<Obstacle> m_Obstacles;
	sf::Clock m_ObstacleSpawnClock;
	sf::Time m_ObstacleSpawnInterval = sf::seconds(2.0f);
	std::mt19937 m_RandomEngine{ std::random_device{}() };

private:
	void SpawnObstacle();
};
