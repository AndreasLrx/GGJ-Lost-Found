/*
** EPITECH PROJECT, 2021
** GGJ AStronaut
** File description:
** Berserk
*/

#include "Entity/Astronauts/Berserk.hpp"
#include "Entity/Alien.hpp"
#include <iostream>

static const int ATTACK_RANGE = 20000;

void Berserk::setAnimationListener()
{
    this->m_sprite.setAnimationEndListener([=](auto sprite){
        (void)sprite;
        if (m_state == MOVE || m_state == IDLE)
            return;
        if (m_state == CAC)
            changeState(IDLE);
    });
}

void Berserk::update(float dt)
{
    float dist;

    Astronaut::update(dt);
    updatePathTimer(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < ATTACK_RANGE && seePos(m_alien->getPosition())) {
        m_path.clear();
        cac();
        return;
    }
    moveToPath(120, dt);
}