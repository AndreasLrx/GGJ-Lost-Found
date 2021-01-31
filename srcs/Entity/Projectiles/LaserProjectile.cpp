/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Laser Projectile entity class
*/

#include "Entity/Projectiles/LaserProjectile.hpp"
#include "GameEngine/Core.hpp"
#include "Entity/Astronauts/Astronaut.hpp"

LaserProjectile::LaserProjectile()
{
    this->m_speed = 1000;
    this->m_activeTime = 1.0f;
}

void LaserProjectile::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::IntRect frames[4] = { {158, 33, 75, 100}, {49, 33, 80, 100}, {508, 33, 105, 100 }, {266, 33, 197, 100} };

    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureFrames(4, frames);
	this->setPosition(pos);
	this->setScale(scale);
    this->m_sprite.update(0);
    this->m_sprite.setAnimationSpeed(10.0f);
    this->m_sprite.setAnimationEndListener([=](auto sprite) {
        this->m_terminalVelocity = true;
    });
    this->m_sprite.setOrigin(sf::Vector2f(150, 95));
}

void LaserProjectile::spawn(Entity* owner, Room *room)
{
    AbstractProjectile::spawn(owner, room);

    sf::SoundBuffer *buffer;
    sf::Sound *sound = new sf::Sound();
    GameDataRef data = this->getGameData();

    if (getRand(0, 100) > 50)
        buffer = data->assets.getSound("piou1");
    else
        buffer = data->assets.getSound("piou2");
    sound->setBuffer(*buffer);
    sound->setPitch(getRand(0.5f, 1.5f));
    sound->play();
    sound->setVolume(20);
    data->assets.keepSound(sound);
}

void LaserProjectile::update(float dt)
{
    AbstractProjectile::update(dt);
    AbstractAstronaut* astronaut = static_cast<Astronaut*>(this->m_owner);
    Alien* alien = astronaut->getAlien();

    if (alien->isAlive() && this->collidesWith(*alien)) {
        this->m_activeTime = 0.0f;
        this->m_isAlive = false;
        alien->takeDamage(1.0f);
    }
}

Circle const* LaserProjectile::getCircleBounds(std::size_t& size) const
{
    size = 1;
    return &this->m_bounds;
}

void LaserProjectile::onPositionChanged()
{
    AbstractProjectile::onPositionChanged();

    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

    this->m_bounds.m_pos = sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.width / 2.0f);
}

void LaserProjectile::onScaleChanged()
{
    AbstractProjectile::onScaleChanged();

    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

    this->m_bounds.m_radius = bounds.height * 0.2;
}


