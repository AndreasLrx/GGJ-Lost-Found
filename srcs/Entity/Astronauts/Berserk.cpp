/*
** EPITECH PROJECT, 2021
** GGJ AStronaut
** File description:
** Berserk
*/

#include "Entity/Astronauts/Berserk.hpp"
#include "Entity/Alien.hpp"

static const int ATTACK_RANGE = 40000;

void Berserk::update(float dt)
{
    float dist;

    if (m_room->getTileAt(this->getPosition()) == nullptr)
        return;
    updatePathTimer(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < ATTACK_RANGE && seePos(m_alien->getPosition())) {
        m_path.clear();
        //attack
        return;
    }
    moveToPath(120, dt);
}