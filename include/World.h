#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Globals.h"

class World
{
public:
    struct Obstacle
    {
        Obstacle(sf::Texture& texture) : m_Sprite(texture), m_AnimationTime(sf::Time::Zero), m_CurrentFrame(0) {}

        sf::Sprite m_Sprite;
        bool m_IsBird = false;
        float m_Speed = 0.f;

        sf::Time m_AnimationTime;
        size_t m_CurrentFrame;
    };
public:
    World();

    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow& window);

    const std::vector<Obstacle>& GetObstacles() const { return m_Obstacles; }
private:
    sf::Texture m_Texture;
    sf::Sprite m_Ground1;
    sf::Sprite m_Ground2;
    float m_GroundY;
    float m_ScrollSpeed = 500.0f;

    std::vector<sf::IntRect> m_CactusRects;
    sf::IntRect m_BirdFrames[2]; // Two frames for bird animation
    const float m_BirdFrameSwitchTime = 0.2f;

    std::vector<Obstacle> m_Obstacles;
    sf::Clock m_ObstacleSpawnClock;
    sf::Time m_ObstacleSpawnInterval = sf::seconds(2.0f);
    std::mt19937 m_RandomEngine{ std::random_device{}() };

private:
    void SpawnObstacle();
};
