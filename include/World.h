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

    struct Cloud
    {
        Cloud(sf::Texture& texture) : m_Sprite(texture) {}

        sf::Sprite m_Sprite;
        float m_Speed = 0.f;
    };
public:
    World();

    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow& window);
    void Reset();

    const std::vector<Obstacle>& GetObstacles() const { return m_Obstacles; }
private:
    sf::Texture m_Texture;
    sf::Sprite m_Ground1;
    sf::Sprite m_Ground2;
    float m_GroundY;

    float m_ScrollSpeed = 500.0f;
    sf::Time m_ScrollSpeedIncreaseInterval = sf::seconds(10.0f);
    sf::Clock m_ScrollSpeedIncreaseClock;
    float m_ScrollSpeedIncrement = 25.0f;

    std::vector<sf::IntRect> m_CactusRects;
    sf::IntRect m_BirdFrames[2]; // Two frames for bird animation
    const float m_BirdFrameSwitchTime = 0.2f;
    const float m_BirdSpeedMultiplier = 1.25f;

    std::vector<Cloud> m_Clouds;
    sf::IntRect m_CloudRect;
    sf::Clock m_CloudSpawnClock;
    sf::Time m_CloudSpawnInterval = sf::seconds(3.f);
    const float m_CloudSpeedMultiplier = 0.15f;

    std::vector<Obstacle> m_Obstacles;
    sf::Clock m_ObstacleSpawnClock;
    sf::Time m_ObstacleSpawnInterval = sf::seconds(2.0f);
    std::mt19937 m_RandomEngine{ std::random_device{}() };

private:
    void SpawnObstacle();
};
