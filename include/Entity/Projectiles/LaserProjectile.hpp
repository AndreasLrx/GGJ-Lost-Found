/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Laser Projectile entity class
*/

#ifndef LASER_PROJECTILE_HPP
#define LASER_PROJECTILE_HPP

#include "Entity/Projectiles/AbstractProjectile.hpp"

class LaserProjectile : public AbstractProjectile
{
public:
    LaserProjectile();

    void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });
    void spawn(Entity* owner, GameDataRef data) override;
};

#endif // !defined(LASER_PROJECTILE_HPP)
