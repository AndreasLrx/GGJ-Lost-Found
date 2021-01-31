/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** Ball Projectile entity class
*/

#include "Entity/Projectiles/BallProjectile.hpp"
#include "GameEngine/Core.hpp"

BallProjectile::BallProjectile()
{
    this->m_speed = 1000.0f;
    this->m_activeTime = 3.0f;
}

void BallProjectile::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    this->m_sprite.setTexture(texture);
    this->m_sprite.setTextureRect(sf::IntRect(0, 0, 144, 129));
    this->m_sprite.setOrigin(sf::Vector2f(75, 60));
	this->setPosition(pos);
	this->setScale(scale);
}

void BallProjectile::spawn(Entity* owner, GameDataRef data)
{
    AbstractProjectile::spawn(owner, data);
    sf::SoundBuffer *buffer = m_data->assets.getSound("shoot_ball");
    sf::Sound *sound = new sf::Sound();

    sound->setBuffer(*buffer);
    sound->setPitch(getRand(0.5f, 1.5f));
    sound->play();
    sound->setVolume(100);
    m_data->assets.keepSound(sound);
}