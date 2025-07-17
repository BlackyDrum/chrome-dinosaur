#include "UI.h"

UI::UI()
    : m_ScoreText(sf::Text(m_Font, "00000", 20)), m_GameOverText(sf::Text(m_Font, "G A M E  O V E R", 30)), m_RestartButton(m_Texture)
{
    if (!m_Font.openFromFile("assets/PressStart2P.ttf"))
        std::cerr << "Failed to load font!\n";

    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load UI texture!\n";

    sf::Color gray(100, 100, 100);

    sf::FloatRect scoreBounds = m_ScoreText.getLocalBounds();
    m_ScoreText.setOrigin(sf::Vector2f(scoreBounds.position.x + scoreBounds.size.x, 0.f));
    m_ScoreText.setPosition(sf::Vector2f(SCREEN_WIDTH - 10.f, 10.f));
    m_ScoreText.setFillColor(gray);

    sf::FloatRect goBounds = m_GameOverText.getLocalBounds();
    m_GameOverText.setOrigin(sf::Vector2f(goBounds.position.x + goBounds.size.x / 2.f, goBounds.position.y + goBounds.size.y / 2.f));
    m_GameOverText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 40.f));
    m_GameOverText.setFillColor(gray);

    m_RestartButtonRect = sf::IntRect(sf::Vector2i(2, 2), sf::Vector2i(71, 63));
    m_RestartButton.setTextureRect(m_RestartButtonRect);
    m_RestartButton.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f - m_RestartButtonRect.size.x / 2.f, SCREEN_HEIGHT / 2.f + 20.f));
}

void UI::SetGameOver(bool isOver)
{
    m_IsGameOver = isOver;
}

void UI::UpdateScoreText()
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(5) << m_Score;
    m_ScoreText.setString(ss.str());
}

void UI::Draw(sf::RenderWindow& window)
{
    window.draw(m_ScoreText);

    if (m_IsGameOver)
    {
        window.draw(m_GameOverText);
        window.draw(m_RestartButton);
    }
}

void UI::Update(sf::Time deltaTime)
{
    if (m_IsGameOver)
        return;

    m_AccumulatedScore += deltaTime.asSeconds();

    if (m_AccumulatedScore >= m_ScoreUpdateInterval)
    {
        m_Score++;
        m_AccumulatedScore = 0.f;
        UpdateScoreText();
    }
}

void UI::Reset()
{
    m_Score = 0;
    m_AccumulatedScore = 0;
    m_IsGameOver = false;
    m_ScoreText.setString("00000");
}