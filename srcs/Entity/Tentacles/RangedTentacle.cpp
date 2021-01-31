/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** An Alien's ranged tentacle
*/

#include "GameEngine/Core.hpp"
#include "GameEngine/macro.hpp"
#include "Entity/Alien.hpp"
#include "Entity/Tentacles/RangedTentacle.hpp"
#include "Entity/Projectiles/BallProjectile.hpp"

RangedTentacle::RangedTentacle()
{
    sf::IntRect frames[4] = { {0, 2000, 500, 500}, {500, 2000, 500, 500}, {1000, 2000, 500, 500}, {1500, 2000, 500, 500} };
    this->m_sprite.setTextureFrames(4, frames);
}

void RangedTentacle::attack(GameDataRef gameData)
{
	if (this->m_cooldown > 0)
		return;

	BallProjectile* ball = new BallProjectile();

	ball->init(*gameData->assets.getTexture("ball"), this->m_owner->getPosition(), sf::Vector2f(0.25, 0.25));
	ball->setOrientation(this->m_owner->getOrientation());
	this->m_owner->spawnProjectile(gameData, ball);
	this->setCooldown(0.6f);
}

