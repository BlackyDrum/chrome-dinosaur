#pragma once

#include <SFML/Graphics.hpp>

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
    const float m_Gravity = 1000.0f;
    const float m_JumpStrength = -400.0f;
    const float m_GroundY = 200.0f;

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
