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

    m_BirdFrames[0] = (sf::IntRect(sf::Vector2i(260, 14), sf::Vector2i(91, 67))); // Flap down
    m_BirdFrames[1] = (sf::IntRect(sf::Vector2i(352, 2), sf::Vector2i(91, 59))); // Flap up

    m_ObstacleSpawnClock.restart();

    m_CloudRect = sf::IntRect(sf::Vector2i(166, 2), sf::Vector2i(91, 26));
    m_CloudSpawnClock.restart();
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

    if (m_ScrollSpeedIncreaseClock.getElapsedTime() >= m_ScrollSpeedIncreaseInterval)
    {
        m_ScrollSpeed += m_ScrollSpeedIncrement;
        m_ScrollSpeedIncreaseClock.restart();

        // Update obstacle speeds
        for (auto& obstacle : m_Obstacles)
        {
            obstacle.m_Speed = obstacle.m_IsBird ? m_ScrollSpeed * m_BirdSpeedMultiplier : m_ScrollSpeed;
        }
    }

    if (m_ObstacleSpawnClock.getElapsedTime() >= m_ObstacleSpawnInterval)
    {
        SpawnObstacle();

        // Set random spawn interval
        std::uniform_real_distribution<float> dist(1.f, 4.f);
        m_ObstacleSpawnInterval = sf::seconds(dist(m_RandomEngine));

        m_ObstacleSpawnClock.restart();
    }

    for (auto& obstacle : m_Obstacles)
    {
        float obstacleSpeed = obstacle.m_Speed * deltaTime.asSeconds();
        obstacle.m_Sprite.move(sf::Vector2f(-obstacleSpeed, 0));

        if (obstacle.m_IsBird)
        {
            // Update bird animation
            obstacle.m_AnimationTime += deltaTime;

            if (obstacle.m_AnimationTime.asSeconds() >= m_BirdFrameSwitchTime)
            {
                obstacle.m_CurrentFrame = (obstacle.m_CurrentFrame + 1) % 2; // Toggle between 0 and 1
                obstacle.m_Sprite.setTextureRect(m_BirdFrames[obstacle.m_CurrentFrame]);
                obstacle.m_AnimationTime = sf::Time::Zero;
            }
        }
    }

    m_Obstacles.erase(std::remove_if(m_Obstacles.begin(), m_Obstacles.end(),
        [](const Obstacle& o) {
            return o.m_Sprite.getPosition().x + o.m_Sprite.getGlobalBounds().size.x < 0;
        }), m_Obstacles.end());

    if (m_CloudSpawnClock.getElapsedTime() >= m_CloudSpawnInterval)
    {
        Cloud cloud(m_Texture);
        cloud.m_Sprite.setTextureRect(m_CloudRect);

        float spawnX = SCREEN_WIDTH + m_CloudRect.size.x;
        std::uniform_real_distribution<float> heightDist(20.f, SCREEN_HEIGHT / 2.f);
        float y = heightDist(m_RandomEngine);

        cloud.m_Sprite.setPosition(sf::Vector2f(spawnX, y));
        cloud.m_Speed = m_ScrollSpeed * m_CloudSpeedMultiplier;

        m_Clouds.push_back(std::move(cloud));

        std::uniform_real_distribution<float> dist(2.f, 5.f);
        m_CloudSpawnInterval = sf::seconds(dist(m_RandomEngine));
        m_CloudSpawnClock.restart();
    }

    for (auto& cloud : m_Clouds)
    {
        float cloudSpeed = cloud.m_Speed * deltaTime.asSeconds();
        cloud.m_Sprite.move(sf::Vector2f(-cloudSpeed, 0));
    }

    m_Clouds.erase(std::remove_if(m_Clouds.begin(), m_Clouds.end(),
        [](const Cloud& c) {
            return c.m_Sprite.getPosition().x + c.m_Sprite.getGlobalBounds().size.x < 0;
        }), m_Clouds.end());
}

void World::Draw(sf::RenderWindow& window)
{
    for (const auto& cloud : m_Clouds)
    {
        window.draw(cloud.m_Sprite);
    }

    window.draw(m_Ground1);
    window.draw(m_Ground2);

    for (const auto& obstacle : m_Obstacles)
    {
        window.draw(obstacle.m_Sprite);
    }
}

void World::SpawnObstacle()
{
    std::uniform_int_distribution<uint32_t> dist(0, 9); // 0-7 = cactus, 8-9 = bird
    uint32_t roll = dist(m_RandomEngine);
    uint32_t type = (roll < 8) ? 0 : 1; // 80% chance for cactus, 20% for bird

    Obstacle obstacle(m_Texture);

    if (type == 0)
    {
        size_t index = std::rand() % m_CactusRects.size();
        obstacle.m_Sprite.setTextureRect(m_CactusRects[index]);
        
        float spawnX = SCREEN_WIDTH + m_CactusRects[index].size.x; // Spawn off-screen
        float offsetY = 20.0f;
        float y = static_cast<float>(m_GroundY - m_CactusRects[index].size.y + offsetY);
        obstacle.m_Sprite.setPosition(sf::Vector2f(spawnX, y));
        obstacle.m_Speed = m_ScrollSpeed;
    }
    else if (type == 1)
    {
        size_t frame = 0;
        obstacle.m_IsBird = true;
        obstacle.m_CurrentFrame = frame;
        obstacle.m_AnimationTime = sf::Time::Zero;

        obstacle.m_Sprite.setTextureRect(m_BirdFrames[frame]);

        float spawnX = SCREEN_WIDTH + m_BirdFrames[0].size.x;
        float lowY = static_cast<float>(m_GroundY - m_BirdFrames[0].size.y); // player must jump
        float highY = static_cast<float>(m_GroundY - m_BirdFrames[0].size.y - 40.0f); // player must duck

        std::uniform_int_distribution<uint32_t> heightDist(0, 1);
        float y = (heightDist(m_RandomEngine) == 0) ? lowY : highY;

        obstacle.m_Sprite.setPosition(sf::Vector2f(spawnX, y));
        obstacle.m_Speed = m_ScrollSpeed * m_BirdSpeedMultiplier;
    }

    m_Obstacles.push_back(std::move(obstacle));
}

void World::Reset()
{
    m_Ground1.setPosition(sf::Vector2f(0, m_GroundY));
    m_Ground2.setPosition(sf::Vector2f(m_Ground1.getPosition().x + m_Ground1.getGlobalBounds().size.x, m_GroundY));

    m_Obstacles.clear();
    m_ObstacleSpawnClock.restart();

    m_Clouds.clear();
    m_CloudSpawnClock.restart();

    m_ScrollSpeed = 500.0f;
    m_ScrollSpeedIncreaseClock.restart();
}