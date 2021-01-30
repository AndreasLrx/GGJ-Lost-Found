/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Laser Projectile entity class
*/

#include "Entity/Projectiles/LaserProjectile.hpp"

LaserProjectile::LaserProjectile()
{
    this->m_speed = 3000;
    this->m_activeTime = 1.0f;
}

void LaserProjectile::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureRect(sf::IntRect(0, 0, 96, 8));
    this->m_sprite.setOrigin(sf::Vector2f(0, 3));
	this->setPosition(pos);
	this->setScale(scale);
}
