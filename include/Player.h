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
    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetBounds() const;
private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;

    float m_VelocityY = 0.0;
    const float m_Gravity = 5000.0f;
    const float m_JumpStrength = -1500.0f;
    const float m_GroundY = SCREEN_HEIGHT;

	const uint32_t m_SpriteWidth = 87;
	const uint32_t m_SpriteHeight = 95;

    // Animation frames
	size_t m_RunFrameCount = 3;
    sf::IntRect m_RunFrames[3];
    uint32_t m_CurrentFrame = 0;
    const float m_FrameSwitchTime = 0.08f;
    sf::Clock m_AnimationClock;

private:
    void m_UpdateAnimation();
    void m_ApplyGravity(sf::Time deltaTime);
};
