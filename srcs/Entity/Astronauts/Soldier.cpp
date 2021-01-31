/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Shooter
*/

#include <iostream>
#include "Entity/Alien.hpp"
#include "Entity/Astronauts/Soldier.hpp"

static const int SHOOT_RANGE = 160000;
static const int CAC_MOD_RANGE = 70000;
static const int CAC_RANGE = 30000;

void Soldier::update(float dt)
{
    float dist;

    Astronaut::update(dt);
    if (m_room->getTileAt(this->getPosition()) == nullptr)
        return;
    updatePathTimer(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < SHOOT_RANGE && seePos(m_alien->getPosition())) {
        if (dist < CAC_RANGE) {
            m_path.clear();
            //attack cac
        } else if (dist > CAC_MOD_RANGE) {
            //shoot
            return;
        }
    }
    moveToPath(180, dt);
}

