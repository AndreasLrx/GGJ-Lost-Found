/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Ball Projectile entity class
*/

#include "Entity/Projectiles/BallProjectile.hpp"
#include "Map/Room.hpp"
#include "Entity/Astronauts/Astronaut.hpp"
#include "GameEngine/Core.hpp"

BallProjectile::BallProjectile()
{
    this->m_speed = 1000.0f;
    this->m_activeTime = 3.0f;
    this->m_bounds = Circle();
}

void BallProjectile::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::IntRect frames = { 0, 0, 144, 129 };

    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureFrames(1, &frames);
    this->m_sprite.setOrigin(sf::Vector2f(80, 60));
	this->setPosition(pos);
	this->setScale(scale);
    this->m_sprite.update(0);
    this->m_sprite.setAnimationEndListener([=](auto sprite) {
        this->m_terminalVelocity = true;
    });
}

void BallProjectile::onPositionChanged()
{
    AbstractProjectile::onPositionChanged();

    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

    this->m_bounds.m_pos = sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.width / 2.0f);
}

void BallProjectile::onScaleChanged()
{
    AbstractProjectile::onScaleChanged();

    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

    this->m_bounds.m_radius = bounds.width * 0.1;
}

void BallProjectile::spawn(Entity* owner, Room *room)
{
    AbstractProjectile::spawn(owner, room);
    sf::SoundBuffer *buffer = this->getGameData()->assets.getSound("shoot_ball");
    sf::Sound *sound = new sf::Sound();

    sound->setBuffer(*buffer);
    sound->setPitch(getRand(0.5f, 1.5f));
    sound->play();
    sound->setVolume(100);
    this->getGameData()->assets.keepSound(sound);
}

void BallProjectile::update(float dt)
{
    AbstractProjectile::update(dt);
    std::vector<Astronaut*> &astronauts = this->m_room->getAstronauts();

    for (auto it = astronauts.begin(); it < astronauts.end(); ++it) {
        if (this->collidesWith(**it)) {
            this->m_activeTime = 0.0f;
            this->m_isAlive = false;
            (*it)->takeDamage(1.0f);
            break;
        }
    }
}

Circle const* BallProjectile::getCircleBounds(std::size_t& size) const
{
    size = 1;
    return &this->m_bounds;
}
