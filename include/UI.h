#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include "Globals.h"

class UI
{
public:
    UI();

    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow& window);

    void Reset();
    void SetGameOver(bool isGameOver);

    sf::FloatRect GetRestartButtonBounds() const { return m_RestartButton.getGlobalBounds(); }

    uint32_t GetScore() const { return m_Score; }
private:
    sf::Font m_Font;
    
    sf::Text m_HighScoreText;
    uint32_t m_HighScore = 0;
    const std::string m_HighScoreFile = "data/highscore.txt";

    sf::Text m_ScoreText;
    uint32_t m_Score = 0;
    float m_AccumulatedScore = 0.f;
    float m_ScoreUpdateInterval = 0.1f;

    sf::Text m_GameOverText;
    sf::Sprite m_RestartButton;
    sf::Texture m_Texture;
    sf::IntRect m_RestartButtonRect;
    bool m_IsGameOver = false;
private:
    void UpdateScoreText();
};