#include "World.h"

World::World()
	: m_Texture(), m_Ground1(m_Texture), m_Ground2(m_Texture)
{
    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load world texture!" << std::endl;

    sf::IntRect groundRect(sf::Vector2i(2, 104), sf::Vector2i(2400, 23));

    uint32_t offsetY = 5;
	m_GroundY = SCREEN_HEIGHT - groundRect.size.y - offsetY;

    m_Ground1.setTextureRect(groundRect);
    m_Ground1.setPosition(sf::Vector2f(0, m_GroundY));

    m_Ground2.setTextureRect(groundRect);
	m_Ground2.setPosition(sf::Vector2f(m_Ground1.getPosition().x + m_Ground1.getGlobalBounds().size.x, m_GroundY));
}

void World::Update(sf::Time deltaTime)
{
    float move = m_ScrollSpeed * deltaTime.asSeconds();

	// Move the ground sprites to create a scrolling effect
    m_Ground1.move(sf::Vector2f(-move, 0));
    m_Ground2.move(sf::Vector2f(-move, 0));

    // Reset ground position when off-screen
    if (m_Ground1.getPosition().x + m_Ground1.getGlobalBounds().size.x < 0)
        m_Ground1.setPosition(sf::Vector2f(m_Ground2.getPosition().x + m_Ground2.getGlobalBounds().size.x, m_GroundY));

    if (m_Ground2.getPosition().x + m_Ground2.getGlobalBounds().size.x < 0)
        m_Ground2.setPosition(sf::Vector2f(m_Ground1.getPosition().x + m_Ground1.getGlobalBounds().size.x, m_GroundY));
}

void World::Draw(sf::RenderWindow& window)
{
    window.draw(m_Ground1);
    window.draw(m_Ground2);
}

sf::FloatRect World::GetBounds() const
{
    return m_Ground1.getGlobalBounds();
}
