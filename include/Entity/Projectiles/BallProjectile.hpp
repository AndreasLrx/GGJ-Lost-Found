/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Ball Projectile entity class
*/

#ifndef BALL_PROJECTILE_HPP
#define BALL_PROJECTILE_HPP

#include "Entity/Projectiles/AbstractProjectile.hpp"

class BallProjectile : public AbstractProjectile
{
public:
    BallProjectile();

    void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });
    void spawn(Entity* owner, GameDataRef data) override;
};

#endif // !defined(BALL_PROJECTILE_HPP)
