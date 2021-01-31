/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** An Alien's shield tentacle
*/

#include "Entity/Tentacles/ShieldTentacle.hpp"

ShieldTentacle::ShieldTentacle()
{
    sf::IntRect frames[4] = { {0, 1500, 500, 500}, {500, 1500, 500, 500}, {1000, 1500, 500, 500}, {1500, 1500, 500, 500} };
    this->m_sprite.setTextureFrames(4, frames);
    this->m_maxHealth = 2.0f;
    this->m_health = 2.0f;
}

