#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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
private:
    sf::Font m_Font;
    sf::Text m_ScoreText;
    sf::Text m_GameOverText;

    uint32_t m_Score = 0;
    float m_AccumulatedScore = 0.f;
    float m_ScoreUpdateInterval = 0.1f;

    sf::Sprite m_RestartButton;
    sf::Texture m_Texture;
    sf::IntRect m_RestartButtonRect;
    bool m_IsGameOver = false;
private:
    void UpdateScoreText();
};