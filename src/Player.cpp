#include "Player.h"

Player::Player()
    : m_Texture(), m_Sprite(m_Texture)
{
    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load sprite sheet\n";

    m_RunFrames[0] = sf::IntRect(sf::Vector2i(1338, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));
    m_RunFrames[1] = sf::IntRect(sf::Vector2i(1514, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));
    m_RunFrames[2] = sf::IntRect(sf::Vector2i(1602, 0), sf::Vector2i(m_SpriteWidth, m_SpriteHeight));

    m_DuckFrames[0] = sf::IntRect(sf::Vector2i(1866, 36), sf::Vector2i(m_DuckSpriteWidth, m_DuckSpriteHeight));
    m_DuckFrames[1] = sf::IntRect(sf::Vector2i(1984, 36), sf::Vector2i(m_DuckSpriteWidth, m_DuckSpriteHeight));

    m_DeadFrame = sf::IntRect(sf::Vector2i(1782, 6), sf::Vector2i(79, 85));

    m_Sprite.setTextureRect(m_RunFrames[0]);
    m_Sprite.setPosition(sf::Vector2f(m_XPosition, m_GroundY - m_Sprite.getGlobalBounds().size.y));
}

void Player::Update(sf::Time deltaTime)
{
    ApplyGravity(deltaTime);
    UpdateAnimation();

    m_Sprite.move(sf::Vector2f(0, m_VelocityY * deltaTime.asSeconds()));

    float maxY = m_GroundY - m_Sprite.getGlobalBounds().size.y;
    if (m_Sprite.getPosition().y > maxY)
    {
        m_Sprite.setPosition(sf::Vector2f(m_Sprite.getPosition().x, maxY));
        m_VelocityY = 0.0f;
    }
}

bool Player::Jump()
{
    float maxY = m_GroundY - m_Sprite.getGlobalBounds().size.y;
    if (m_Sprite.getPosition().y >= maxY - 1.0f)
    {
        m_Sprite.setTextureRect(m_RunFrames[0]);
        m_VelocityY = m_JumpStrength;

        return true;
    }

    return false;
}

void Player::Duck()
{
    if (m_IsDucking || IsInAir())
        return;

    m_IsDucking = true;
    m_CurrentFrame = 0;

    m_Sprite.setTextureRect(m_DuckFrames[m_CurrentFrame]);
    
    float newHeight = m_Sprite.getGlobalBounds().size.y;
    float y = m_GroundY - newHeight;
    m_Sprite.setPosition(sf::Vector2f(m_Sprite.getPosition().x, y));
}

void Player::Unduck()
{
    if (!m_IsDucking)
        return;

    m_IsDucking = false;
    m_CurrentFrame = 0;

    m_Sprite.setTextureRect(m_RunFrames[m_CurrentFrame]);

    float newHeight = m_Sprite.getGlobalBounds().size.y;
    float y = m_GroundY - newHeight;
    m_Sprite.setPosition(sf::Vector2f(m_Sprite.getPosition().x, y));
}

void Player::Death()
{
    m_IsDead = true;
    m_Sprite.setTextureRect(m_DeadFrame);

    if (m_IsDucking)
    {
        m_IsDucking = false;

        float newHeight = m_Sprite.getGlobalBounds().size.y;
        float y = m_GroundY - newHeight;
        m_Sprite.setPosition(sf::Vector2f(m_Sprite.getPosition().x, y));
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_Sprite);
}

void Player::ApplyGravity(sf::Time deltaTime)
{
    m_VelocityY += m_Gravity * deltaTime.asSeconds();
}

bool Player::IsInAir() const
{
    return m_Sprite.getPosition().y < m_GroundY - m_Sprite.getGlobalBounds().size.y;
}

void Player::UpdateAnimation()
{
    if (IsInAir())
    {
        m_CurrentFrame = 0;
        m_Sprite.setTextureRect(m_RunFrames[m_CurrentFrame]);
    }
    else if (m_AnimationClock.getElapsedTime().asSeconds() >= m_FrameSwitchTime)
    {
        m_AnimationClock.restart();
        m_CurrentFrame = (m_CurrentFrame + 1) % m_RunFrameCount;

        if (m_IsDucking)
            m_Sprite.setTextureRect(m_DuckFrames[m_CurrentFrame % m_DuckFrameCount]);
        else
            m_Sprite.setTextureRect(m_RunFrames[m_CurrentFrame]);
    }
}

void Player::Reset()
{
    m_IsDead = false;
    m_IsDucking = false;
    m_VelocityY = 0.0f;

    m_Sprite.setPosition(sf::Vector2f(m_XPosition, m_GroundY - m_Sprite.getGlobalBounds().size.y));
    m_Sprite.setTextureRect(m_RunFrames[0]);
    m_AnimationClock.restart();
}
