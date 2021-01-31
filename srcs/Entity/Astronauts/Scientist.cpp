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

void Scientist::setAnimationListener()
{
    this->m_sprite.setAnimationEndListener([=](auto sprite){
        (void)sprite;
        if (m_state == MOVE || m_state == IDLE)
            return;
        if (m_state == MOVE_SHOOT)
            changeState(MOVE);
        if (m_state == SHOOT)
            changeState(IDLE);
    });
}

void Scientist::update(float dt)
{
    float dist;
    int seePlayer = seePos(m_alien->getPosition());

    Astronaut::update(dt);
    if (m_room->getTileAt(this->getPosition()) == nullptr)
        return;
    updatePathTimer(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < SHOOT_RANGE && seePlayer) {
        if (dist < FLEE_RANGE) {
            m_path.clear();
            if (m_running == 0) {
                changeState(MOVE);
                runAway(m_alien->getPosition());
            }
            m_running = 1;
            this->move(m_move * dt);
            shoot();
            Tile *tile = m_room->getTileAt(this->getPosition());
            if (tile == nullptr)
                this->move(m_move * -dt);
        } else {
            if (m_state == MOVE)
                changeState(IDLE);
            m_running = 0;
            shoot();
        }
    } else {
        m_running = 0;
        if (!m_path.empty() && m_state == IDLE)
            changeState(MOVE);
        moveToPath(250, dt);
    }
}