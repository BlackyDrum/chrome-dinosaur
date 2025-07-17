#include "UI.h"

UI::UI()
    : m_ScoreText(sf::Text(m_Font, "00000", 20)), m_GameOverText(sf::Text(m_Font, "G A M E  O V E R", 30)), m_HighScoreText(sf::Text(m_Font, "HI 00000", 20)), m_RestartButton(m_Texture)
{
    if (!m_Font.openFromFile("assets/PressStart2P.ttf"))
        std::cerr << "Failed to load font!\n";

    if (!m_Texture.loadFromFile("assets/sprite.png"))
        std::cerr << "Failed to load sprite sheet!\n";

    sf::Color gray(100, 100, 100);

    sf::FloatRect scoreBounds = m_ScoreText.getLocalBounds();
    m_ScoreText.setOrigin(sf::Vector2f(scoreBounds.position.x + scoreBounds.size.x, 0.f));
    m_ScoreText.setPosition(sf::Vector2f(SCREEN_WIDTH - 10.f, 10.f));
    m_ScoreText.setFillColor(gray);

    sf::FloatRect highScoreBounds = m_HighScoreText.getLocalBounds();
    float spacing = 20.f; // Spacing between score and high score
    m_HighScoreText.setOrigin(sf::Vector2f(highScoreBounds.position.x + highScoreBounds.size.x, 0.f));
    m_HighScoreText.setPosition(sf::Vector2f(SCREEN_WIDTH - 10.f - scoreBounds.size.x - spacing, 10.f));
    m_HighScoreText.setFillColor(gray);

    std::ifstream highScoreFile(m_HighScoreFile);
    if (highScoreFile.is_open())
    {
        highScoreFile >> m_HighScore;
        highScoreFile.close();

        if (m_HighScore > 99999)
            m_HighScore = 99999;
    }
    else
    {
        std::cerr << "Failed to open high score file!\n";
        m_HighScore = 0;
    }

    UpdateScoreText();

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

    if (m_IsGameOver && m_Score > m_HighScore)
    {
        m_HighScore = m_Score;
        std::ofstream highScoreFile(m_HighScoreFile);
        if (highScoreFile.is_open())
        {
            highScoreFile << m_HighScore;
            highScoreFile.close();
        }
        else
        {
            std::cerr << "Failed to save high score!\n";
        }

        UpdateScoreText();
    }
}

void UI::UpdateScoreText()
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(5) << m_Score;
    m_ScoreText.setString(ss.str());

    std::stringstream ssHighScore;
    ssHighScore << std::setfill('0') << std::setw(5) << m_HighScore;
    m_HighScoreText.setString("HI " + ssHighScore.str());
}

void UI::Draw(sf::RenderWindow& window)
{
    window.draw(m_ScoreText);
    window.draw(m_HighScoreText);

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
    }

    UpdateScoreText();
}

void UI::Reset()
{
    m_Score = 0;
    m_AccumulatedScore = 0;
    m_IsGameOver = false;
    m_ScoreText.setString("00000");

    UpdateScoreText();
}