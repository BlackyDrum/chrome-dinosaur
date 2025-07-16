#include "Player.h"

Player::Player()
	: m_Texture(), m_Sprite(m_Texture)
{
    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load sprite sheet" << std::endl;

    m_RunFrames[0] = sf::IntRect(sf::Vector2i(1338, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));
    m_RunFrames[1] = sf::IntRect(sf::Vector2i(1514, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));
    m_RunFrames[2] = sf::IntRect(sf::Vector2i(1602, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));

    m_Sprite.setTextureRect(m_RunFrames[0]);

	m_Sprite.setPosition(sf::Vector2f(100.f, m_GroundY - m_Sprite.getGlobalBounds().size.y));
}

void Player::Update(sf::Time deltaTime)
{
    m_ApplyGravity(deltaTime);
    m_UpdateAnimation();

    m_Sprite.move(sf::Vector2f(0, m_VelocityY * deltaTime.asSeconds()));

    float maxY = m_GroundY - m_Sprite.getGlobalBounds().size.y;
    if (m_Sprite.getPosition().y > maxY)
    {
        m_Sprite.setPosition(sf::Vector2f(m_Sprite.getPosition().x, maxY));
        m_VelocityY = 0.0f;
    }
}

void Player::Jump()
{
    float maxY = m_GroundY - m_Sprite.getGlobalBounds().size.y;
    if (m_Sprite.getPosition().y >= maxY - 1.0f)
    {
        m_Sprite.setTextureRect(m_RunFrames[0]);
        m_VelocityY = m_JumpStrength;
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_Sprite);
}

sf::FloatRect Player::GetBounds() const
{
    return m_Sprite.getGlobalBounds();
}

void Player::m_ApplyGravity(sf::Time deltaTime)
{
    m_VelocityY += m_Gravity * deltaTime.asSeconds();
}

void Player::m_UpdateAnimation()
{
    // check if player is in the air
	if (m_Sprite.getPosition().y < m_GroundY - m_Sprite.getGlobalBounds().size.y)
	{
		m_CurrentFrame = 0;
		m_Sprite.setTextureRect(m_RunFrames[m_CurrentFrame]);
	}
	else if (m_AnimationClock.getElapsedTime().asSeconds() >= m_FrameSwitchTime)
    {
        m_AnimationClock.restart();
        m_CurrentFrame = (m_CurrentFrame + 1) % m_RunFrameCount;
        m_Sprite.setTextureRect(m_RunFrames[m_CurrentFrame]);
    }
}
