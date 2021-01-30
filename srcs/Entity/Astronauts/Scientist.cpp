/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Scientist
*/

#include "Entity/Astronauts/Scientist.hpp"
#include "Entity/Alien.hpp"

void Scientist::update(float dt)
{
    this->m_sprite.update(dt);
    m_pathUpdateTimer += dt;
    if (m_pathUpdateTimer >= 1) {
        m_pathUpdateTimer = 0;
        runAway(m_alien->getPosition());
    }
    this->move(m_move * dt);
}