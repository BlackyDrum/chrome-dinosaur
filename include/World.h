#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"

class World
{
public:
    World();

    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetBounds() const;

private:
    sf::Texture m_Texture;
    sf::Sprite m_Ground1;
    sf::Sprite m_Ground2;
    float m_GroundY;

    float m_ScrollSpeed = 200.0f;
};
