/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Laser Projectile entity class
*/

#include "Entity/Projectiles/LaserProjectile.hpp"
#include "GameEngine/Core.hpp"

LaserProjectile::LaserProjectile()
{
    this->m_speed = 1000;
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
}
