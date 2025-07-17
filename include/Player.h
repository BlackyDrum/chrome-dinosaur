#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class Player
{
public:
    Player();

    void Update(sf::Time deltaTime);
    void Jump();
    void Duck();
    void Unduck();
    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetBounds() const;
private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;

    float m_VelocityY = 0.0;
    const float m_Gravity = 5000.0f;
    const float m_JumpStrength = -1500.0f;
    const float m_GroundY = SCREEN_HEIGHT;

    bool m_IsDucking = false;
    size_t m_DuckFrameCount = 2;
    sf::IntRect m_DuckFrames[2];

    const uint32_t m_SpriteWidth = 87;
    const uint32_t m_SpriteHeight = 95;

    const uint32_t m_DuckSpriteWidth = 117;
    const uint32_t m_DuckSpriteHeight = 59;

    size_t m_RunFrameCount = 3;
    sf::IntRect m_RunFrames[3];
    uint32_t m_CurrentFrame = 0;
    const float m_FrameSwitchTime = 0.08f;
    sf::Clock m_AnimationClock;
private:
    void UpdateAnimation();
    void ApplyGravity(sf::Time deltaTime);
};
