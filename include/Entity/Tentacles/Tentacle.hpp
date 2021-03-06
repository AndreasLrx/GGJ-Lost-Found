/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** An Alien's tentacle
*/

#ifndef TENTACLE_HPP
#define TENTACLE_HPP

#include <SFML/Graphics.hpp>
#include <math.h>
#include "GameEngine/macro.hpp"
#include "Entity/AnimatedSprite.hpp"

class Alien;

class Tentacle: public sf::Drawable
{
public:
    Tentacle();
    void attach(Alien* owner, sf::Texture const& texture);
    float absorbDamage(float damage);
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    void setScale(sf::Vector2f scale);
    void setScale(float sx, float sy);
    void setOrientation(float angle);
    void setMirrored(bool mirrored);

    void setTentacleIndex(std::size_t index, std::size_t count);

    virtual void attack() {}
    virtual void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    Alien* m_owner = nullptr;
    float m_health;
    float m_maxHealth;
    AnimatedSprite m_sprite;
    float m_cooldownMax = 0.0f;
    float m_cooldown = 0.0f;
    sf::Vector2f m_scale;

    void setCooldown(float cooldown);
};

inline void Tentacle::setPosition(sf::Vector2f pos)
{
    this->m_sprite.setPosition(pos);
}

inline void Tentacle::setPosition(float x, float y)
{
    this->m_sprite.setPosition(x, y);
}

inline void Tentacle::setScale(float sx, float sy)
{
    this->m_sprite.setScale(sx, sy);
}

inline void Tentacle::setMirrored(bool mirrored)
{
    this->m_sprite.setMirrored(mirrored);
}

inline void Tentacle::setOrientation(float angle)
{
    this->m_sprite.setRotation(angle);
}

#endif // !defined(TENTACLE_HPP)
