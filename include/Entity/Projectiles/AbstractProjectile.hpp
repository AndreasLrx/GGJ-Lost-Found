/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** AbstractProjectile entity class
*/

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity/Entity.hpp"

class AbstractProjectile : public Entity
{
public:
    AbstractProjectile();

    virtual void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 }) = 0;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void onPositionChanged() override;
    void onScaleChanged() override;
    void onOrientationChanged() override;
    void spawn(Entity* owner);

protected:
    float m_speed = 1.0f;
    float m_activeTime = 1.0f;
    sf::Sprite m_sprite;
    Entity* m_owner;
};

#endif // !defined(PROJECTILE_HPP)
