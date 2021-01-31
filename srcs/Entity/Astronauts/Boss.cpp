/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Boss
*/

#include "Entity/Astronauts/Boss.hpp"

static const int SHOOT_RANGE = 160000;
static const int CAC_MOD_RANGE = 70000;
static const int CAC_RANGE = 20000;

void Boss::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::FloatRect bounds;
    sf::IntRect *move = new sf::IntRect[4]{{0, 0, 550, 550}, {550, 0, 550, 550}, {1100, 0, 550, 550}, {1650, 0, 550, 550}};
    sf::IntRect *idle = new sf::IntRect[1]{{0, 550, 550, 550}};
    sf::IntRect *cac = new sf::IntRect[1]{{550, 550, 550, 550}};
    sf::IntRect *shoot = new sf::IntRect[1]{{1100, 550, 550, 550}};
	sf::IntRect *move_shoot = new sf::IntRect[4]{{0, 1100, 550, 550}, {550, 1100, 550, 550}, {1100, 1100, 550, 550}, {1650, 1100, 550, 550}};
    m_animTextRectTabs[MOVE] = move;
    m_animTextRectTabs[IDLE] = idle;
    m_animTextRectTabs[CAC] = cac;
    m_animTextRectTabs[SHOOT] = shoot;
    m_animTextRectTabs[MOVE_SHOOT] = move_shoot;
    m_animDatas[MOVE] = {3.f, 4};
    m_animDatas[IDLE] = {3.f, 1};
    m_animDatas[CAC] = {3.f, 1};
    m_animDatas[SHOOT] = {1.f, 1};
    m_animDatas[MOVE_SHOOT] = {3.f, 4};

    m_move = sf::Vector2f(0, 0);
    m_running = 0;
    m_state = MOVE;
    m_attackCooldown = 0;
    this->m_sprite.setTexture(texture);
    this->m_sprite.setPosition(pos);
    this->m_sprite.setScale(scale);
    this->changeState(MOVE);
    this->setPosition(pos);
    this->setScale(scale);
    m_sprite.update(0);
    bounds = m_sprite.getLocalBounds();
    this->m_sprite.setOrigin(bounds.width / 2.f, bounds.height);
    this->m_sprite.setMirrored(true);
    setAnimationListener();
}

void Boss::update(float dt)
{
    float dist;

    Astronaut::update(dt);
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
    moveToPath(70, dt);
}
#include <iostream>
void Boss::takeDamage()
{
    m_lifes--;
    if (m_lifes < 0)
        m_isAlive = false;
}