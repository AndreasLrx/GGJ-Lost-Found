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


void Soldier::setAnimationListener()
{
    this->m_sprite.setAnimationEndListener([=](auto sprite){
        if (m_state == MOVE || m_state == IDLE)
            return;
        if (m_state == MOVE_SHOOT)
            changeState(MOVE);
        if (m_state == CAC || m_state == SHOOT)
            changeState(IDLE);
    });
}

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
            cac();
        } else if (dist > CAC_MOD_RANGE) {
            if (m_state != SHOOT && m_state != MOVE_SHOOT) {
                changeState(IDLE);
                shoot();
            }
            return;
        }
    }
    if (!m_path.empty() && m_state == IDLE)
        changeState(MOVE);
    moveToPath(180, dt);
}

