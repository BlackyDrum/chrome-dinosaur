#include "World.h"

World::World()
    : m_Texture(), m_Ground1(m_Texture), m_Ground2(m_Texture)
{
    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load world texture!" << std::endl;

    std::srand(static_cast<uint32_t>(std::time(nullptr)));

    // Initialize ground
    sf::IntRect groundRect(sf::Vector2i(2, 104), sf::Vector2i(2400, 23));

    uint32_t offsetY = 5;
    m_GroundY = SCREEN_HEIGHT - groundRect.size.y - offsetY;

    m_Ground1.setTextureRect(groundRect);
    m_Ground1.setPosition(sf::Vector2f(0, m_GroundY));

    m_Ground2.setTextureRect(groundRect);
    m_Ground2.setPosition(sf::Vector2f(m_Ground1.getPosition().x + m_Ground1.getGlobalBounds().size.x, m_GroundY));

    // Initialize obstacles
    m_CactusRects.push_back(sf::IntRect(sf::Vector2i(446, 2), sf::Vector2i(33, 69)));
    m_CactusRects.push_back(sf::IntRect(sf::Vector2i(480, 2), sf::Vector2i(67, 69)));
    m_CactusRects.push_back(sf::IntRect(sf::Vector2i(548, 2), sf::Vector2i(101, 69)));
    m_CactusRects.push_back(sf::IntRect(sf::Vector2i(652, 2), sf::Vector2i(49, 99)));

    m_ObstacleSpawnClock.restart();
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

    if (m_ObstacleSpawnClock.getElapsedTime() >= m_ObstacleSpawnInterval)
    {
        SpawnObstacle();

        // Set random spawn interval
        std::uniform_real_distribution<float> dist(1.5f, 4.f);
        m_ObstacleSpawnInterval = sf::seconds(dist(m_RandomEngine));

        m_ObstacleSpawnClock.restart();
    }

    for (auto& obstacle : m_Obstacles)
    {
        obstacle.sprite.move(sf::Vector2f(-move, 0));
    }

    m_Obstacles.erase(std::remove_if(m_Obstacles.begin(), m_Obstacles.end(),
        [](const Obstacle& o) {
            return o.sprite.getPosition().x + o.sprite.getGlobalBounds().size.x < 0;
        }), m_Obstacles.end());
}

void World::Draw(sf::RenderWindow& window)
{
    window.draw(m_Ground1);
    window.draw(m_Ground2);

    for (const auto& obstacle : m_Obstacles)
    {
        window.draw(obstacle.sprite);
    }
}

sf::FloatRect World::GetBounds() const
{
    return m_Ground1.getGlobalBounds();
}

void World::SpawnObstacle()
{
    std::uniform_int_distribution<uint32_t> dist(0, 1); // 0 = cactus, 1 = bird
    uint32_t type = 0; //dist(m_RandomEngine);

    Obstacle obstacle(m_Texture);

    if (type == 0) // Cactus
    {
        size_t index = std::rand() % m_CactusRects.size();
        obstacle.sprite.setTextureRect(m_CactusRects[index]);
        
        float spawnX = SCREEN_WIDTH + m_CactusRects[index].size.x; // Spawn off-screen
        float offsetY = 20.0f;
        float y = static_cast<float>(m_GroundY - m_CactusRects[index].size.y + offsetY);
        obstacle.sprite.setPosition(sf::Vector2f(spawnX, y));
    }

    m_Obstacles.push_back(std::move(obstacle));
}