#include "SoundManager.h"

SoundManager::SoundManager()
    : m_JumpSound(m_JumpBuffer), m_DieSound(m_DieBuffer), m_ScoreSound(m_ScoreBuffer)
{
    if (!m_JumpBuffer.loadFromFile("assets/sounds/jump.wav") ||
        !m_DieBuffer.loadFromFile("assets/sounds/die.wav") ||
        !m_ScoreBuffer.loadFromFile("assets/sounds/point.wav"))
    {
        std::cerr << "Failed to load sound files!\n";
    }
}

void SoundManager::PlayJumpSound()
{
    m_JumpSound.play();
}

void SoundManager::PlayDieSound()
{
    m_DieSound.play();
}

void SoundManager::PlayScoreSound()
{
    m_ScoreSound.play();
}