/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Shooter
*/

#include <iostream>
#include "Entity/Alien.hpp"
#include "Entity/Astronauts/Shooter.hpp"

static const int SHOOT_RANGE = 160000;
static const int FLEE_RANGE = 70000;

void Shooter::update(float dt)
{
    float dist;

    if (m_room->getTileAt(this->getPosition()) == nullptr)
        return;
    if (m_pathUpdateTimer >= 1) {
        m_pathUpdateTimer = 0;
        if (m_running)
            runAway(m_alien->getPosition());
        else 
            resetPath(m_alien->getPosition());
    }
    m_pathUpdateTimer += dt;
    this->m_sprite.update(dt);
    dist = getDistSquared(this->getPosition(), m_alien->getPosition());
    if (dist < SHOOT_RANGE && seePos(m_alien->getPosition())) {
        m_path.clear();
        //shoot
        if (dist < FLEE_RANGE) {
            if (!m_running)
                runAway(m_alien->getPosition());
            m_running = 1;
            this->move(m_move * dt);
        } else
            m_running = 0;
        return;
    } else {
        m_running = 0;
    }
    if (m_path.size() != 0) {
        unsigned int tileSize = m_room->getTileSize();
        sf::Vector2i nextPos = m_path[m_path.size() - 1];
        sf::Vector2f posTile(nextPos.x * tileSize, nextPos.y * tileSize);
        sf::Vector2f diff = posTile - this->getPosition();
        float lenSquared = diff.x * diff.x + diff.y * diff.y;
        
        if (lenSquared <= 400) {
            m_path.pop_back();
            if (m_path.size() == 0)
                return;
            nextPos = m_path[m_path.size() - 1];
            posTile = sf::Vector2f(nextPos.x * tileSize, nextPos.y * tileSize);
            diff = posTile - this->getPosition();
            lenSquared = diff.x * diff.x + diff.y * diff.y;
        }
        float lenSqrt = sqrt(lenSquared);
        this->move(diff.x * (dt * 200) / lenSqrt, diff.y * dt * 200 / lenSqrt);
    }
}