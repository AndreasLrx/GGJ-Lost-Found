/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Scientist
*/

#include "Entity/Astronauts/Scientist.hpp"
#include "Entity/Alien.hpp"
#include <iostream>

static const int SHOOT_RANGE = 160000;
static const int FLEE_RANGE = 70000;

void Scientist::update(float dt)
{
    float dist;
    int seePlayer = seePos(m_alien->getPosition());

    if (m_room->getTileAt(this->getPosition()) == nullptr)
        return;
    updatePathTimer(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < SHOOT_RANGE && seePlayer) {
        if (dist < FLEE_RANGE) {
            m_path.clear();
            if (!m_running)
                runAway(m_alien->getPosition());
            m_running = 1;
            this->move(m_move * dt);
            Tile *tile = m_room->getTileAt(this->getPosition());
            if (tile == nullptr)
                this->move(m_move * -dt);
        } else {
            //shoot
            m_running = 0;
        }
    } else {
        m_running = 0;
        moveToPath(250, dt);
    }
}