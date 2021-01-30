/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** alien player class
*/

#include <cmath>
#include "GameEngine/Core.hpp"
#include "Entity/Alien.hpp"
#include "States/GameState.hpp"

Alien::Alien(GameDataRef gameData): m_gameData(gameData) {}

Alien::~Alien() {}

void Alien::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
	this->m_bodySprite.setTexture(texture);
	this->m_bodyRect = sf::IntRect(0, 484, 484, 484);
	this->m_bodySprite.setTextureRect(this->m_bodyRect);
	this->m_eyeSprite.setTexture(texture);
	this->m_eyeRect = sf::IntRect(0, 0, 484, 484);
	this->m_eyeSprite.setTextureRect(this->m_eyeRect);
	this->m_slimeSprite.setTexture(texture);
	this->m_slimeRect = sf::IntRect(484, 484, 484, 484);
	this->m_slimeSprite.setTextureRect(this->m_slimeRect);
	this->m_bodySprite.setOrigin(242, 242);
	this->m_eyeSprite.setOrigin(242, 242);
	this->m_slimeSprite.setOrigin(242, 260);
	this->setPosition(pos);
	this->setScale(scale);
}

void Alien::handleInput(sf::Event event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;
	LaserProjectile* laser = new LaserProjectile();

	laser->init(*this->m_gameData->assets.getTexture("laser"), this->getPosition(), sf::Vector2f(2.5, 2.5));
	laser->setOrientation(this->getOrientation());
	this->spawnProjectile(this->m_gameData, laser);
}

void Alien::onPositionChanged()
{
	this->m_bodySprite.setPosition(this->getPosition());
	this->m_eyeSprite.setPosition(this->getPosition());
	this->m_slimeSprite.setPosition(this->getPosition());
}

void Alien::onScaleChanged()
{
	this->m_bodySprite.setScale(this->getScale());
	this->m_eyeSprite.setScale(this->getScale());
	this->m_slimeSprite.setScale(this->getScale());
}

void Alien::onOrientationChanged()
{
	sf::IntRect bodyRect = this->m_bodyRect;
	sf::IntRect eyeRect = this->m_eyeRect;

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(this->m_gameData->wind));
	sf::Vector2f lookVec = this->getPosition() - mousePos;
	float angle = this->getOrientation();
	float range;

	if (sqrtf(lookVec.x * lookVec.x + lookVec.y * lookVec.y) < 100.0f) {
			this->m_eyeRect = sf::IntRect(0, 0, 484, 484);
	} else {
		if (angle >= 90.0f && angle <= 270.0)
			range = angle - 90;
		else if (angle > 270.0f)
			range = 180 - (angle - 270);
		else
			range = 90 - angle;

		if (range < 22.0f)
			this->m_eyeRect = sf::IntRect(972, 0, 484, 484);
		else if (range < 67.5f)
			this->m_eyeRect = sf::IntRect(1936, 0, 484, 484);
		else if (range < 112.5f)
			this->m_eyeRect = sf::IntRect(1452, 0, 484, 484);
		else if (range < 157.0f)
			this->m_eyeRect = sf::IntRect(2420, 0, 484, 484);
		else
			this->m_eyeRect = sf::IntRect(484, 0, 484, 484);
	}
	if (angle >= 270.0f || angle < 90.0f) {
		this->m_bodySprite.setTextureRect(bodyRect);
		this->m_eyeSprite.setTextureRect(eyeRect);
	} else {
		this->m_bodySprite.setTextureRect(sf::IntRect(bodyRect.left + bodyRect.width, bodyRect.top, -bodyRect.width, bodyRect.height));
		this->m_eyeSprite.setTextureRect(sf::IntRect(eyeRect.left + eyeRect.width, eyeRect.top, -eyeRect.width, eyeRect.height));
	}
}

void Alien::update(float dt)
{
	sf::Vector2f offset(0, 0);
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(this->m_gameData->wind));
	sf::Vector2f lookVec = this->getPosition() - mousePos;
	sf::IntRect &slimeRect = this->m_slimeRect;
	float angle = atan2(lookVec.y, lookVec.x);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		offset.y -= 250 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		offset.x -= 250 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		offset.y += 250 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		offset.x += 250 * dt;
	if (this->move(offset)) {
		this->m_slimeRect = sf::IntRect(989, 484, 484, 484);

		if (offset.x < 0)
			this->m_slimeSprite.setTextureRect(sf::IntRect(slimeRect.left + slimeRect.width, slimeRect.top, -slimeRect.width, slimeRect.height));
		else
			this->m_slimeSprite.setTextureRect(slimeRect);
	} else {
		this->m_slimeRect = sf::IntRect(484, 484, 484, 484);
		this->m_slimeSprite.setTextureRect(slimeRect);
	}
	this->setOrientation(angle * 180.0 / 3.141592653589793238463 + 180.0);
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->m_slimeSprite, states);
	target.draw(this->m_bodySprite, states);
	target.draw(this->m_eyeSprite, states);
}
