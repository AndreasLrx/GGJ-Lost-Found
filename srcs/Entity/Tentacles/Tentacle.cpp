/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** An Alien's tentacle
*/

#include "Entity/Tentacles/Tentacle.hpp"

Tentacle::Tentacle():  m_maxHealth(1.0f)
{
    sf::IntRect frames[4] = { {0, 1000, 500, 500}, {500, 1000, 500, 500}, {1000, 1000, 500, 500}, {1500, 1000, 500, 500} };
    this->m_health = this->m_maxHealth;
    this->m_sprite.setTextureFrames(4, frames);
    this->m_sprite.setAnimationSpeed(5.0f);
    this->m_sprite.setOrigin(sf::Vector2f(-200, 250));
}

void Tentacle::attach(Alien* owner, sf::Texture const& texture)
{
    this->m_owner = owner;
    this->m_sprite.setTexture(texture);
}

float Tentacle::absorbDamage(float damage)
{
    float newHealth = fmax(0, this->m_health - damage);
    
    this->m_health = newHealth;
    return this->m_health - newHealth;
}

void Tentacle::update(float dt) {
    if (this->m_sprite.isMirrored())
        this->m_sprite.setOrigin(sf::Vector2f(700, 250));
    else
        this->m_sprite.setOrigin(sf::Vector2f(-200, 250));

    this->m_sprite.update(dt);
}

void Tentacle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->m_sprite, states);
}

void Tentacle::setTentacleIndex(std::size_t index, std::size_t count)
{
    this->m_sprite.setProgress(static_cast<float>(index) / static_cast<float>(count));
}
