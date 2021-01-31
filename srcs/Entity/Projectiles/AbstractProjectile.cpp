/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** AbstractProjectile entity class
*/

#include <cmath>
#include "Entity/Projectiles/AbstractProjectile.hpp"
#include "functions.hpp"

AbstractProjectile::AbstractProjectile(): m_speed(1.0f)
{}

void AbstractProjectile::onPositionChanged()
{
    this->m_sprite.setPosition(this->getPosition());
}

void AbstractProjectile::onScaleChanged()
{
    this->m_sprite.setScale(this->getScale());
}

void AbstractProjectile::onOrientationChanged()
{
    this->m_sprite.setRotation(this->getOrientation());
}

#include <iostream>
void AbstractProjectile::update(float dt)
{
    if (this->m_activeTime <= 0.0f)
        return;

    float angle = toRadians(this->getOrientation());
    sf::Vector2f offset(cosf(angle), sinf(angle));

    this->move(offset * dt * this->m_speed);
    this->m_activeTime -= dt;
    if (this->m_activeTime <= 0.0f) {
        this->m_activeTime = 0.0f;
        this->m_isAlive = false;
    }
}

void AbstractProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->m_activeTime > 0.0f)
        target.draw(this->m_sprite, states);
}

void AbstractProjectile::spawn(Entity* owner, GameDataRef data)
{
    this->m_owner = owner;
    this->m_data = data;
}
