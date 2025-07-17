#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
public:
    SoundManager();

    void PlayJumpSound();
    void PlayDieSound();
    void PlayScoreSound();
private:
    sf::SoundBuffer m_JumpBuffer;
    sf::SoundBuffer m_DieBuffer;
    sf::SoundBuffer m_ScoreBuffer;

    sf::Sound m_JumpSound;
    sf::Sound m_DieSound;
    sf::Sound m_ScoreSound;
};