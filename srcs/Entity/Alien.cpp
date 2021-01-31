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
#include "Entity/Tentacles/Tentacle.hpp"
#include "Entity/Tentacles/RangedTentacle.hpp"
#include "Entity/Tentacles/ShieldTentacle.hpp"

Alien::Alien(GameDataRef gameData): m_gameData(gameData) {
	this->m_passiveTentacles = { new ShieldTentacle(), new RangedTentacle(), new ShieldTentacle(), new Tentacle(), new Tentacle() };
	this->m_active_tentacle = new RangedTentacle();
}

Alien::~Alien() {
	delete this->m_active_tentacle;
}

void Alien::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
	this->m_bodySprite.setTexture(texture);
	this->m_bodyRect = sf::IntRect(0, 500, 500, 500);
	this->m_bodySprite.setTextureRect(this->m_bodyRect);
	this->m_eyeSprite.setTexture(texture);
	this->m_eyeRect = sf::IntRect(0, 0, 500, 500);
	this->m_eyeSprite.setTextureRect(this->m_eyeRect);
	this->m_slimeSprite.setTexture(texture);
	this->m_slimeRect = sf::IntRect(500, 500, 500, 500);
	this->m_slimeSprite.setTextureRect(this->m_slimeRect);
	this->m_bodySprite.setOrigin(250, 170);
	this->m_eyeSprite.setOrigin(250, 170);
	this->m_slimeSprite.setOrigin(250, 180);
	this->setPosition(pos);
	this->setScale(scale);

	this->initTentacle(this->m_active_tentacle, 0, texture, pos, scale);
	for (std::size_t i = 0; i < this->m_passiveTentacles.size(); ++i)
		this->initTentacle(this->m_passiveTentacles[i], i, texture, pos, scale);
	this->spreadTentacles();
	this->update(0);
}

void Alien::handleInput(sf::Event event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;
	this->m_active_tentacle->attack();
}

void Alien::onPositionChanged()
{
	this->m_bodySprite.setPosition(this->getPosition());
	this->m_eyeSprite.setPosition(this->getPosition());
	this->m_slimeSprite.setPosition(this->getPosition());
	this->m_active_tentacle->setPosition(this->getPosition());
	for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++) {
		(*it)->setPosition(this->getPosition());
		(*it)->setMirrored(true);
	}
}

void Alien::onScaleChanged()
{
	this->m_bodySprite.setScale(this->getScale());
	this->m_eyeSprite.setScale(this->getScale());
	this->m_slimeSprite.setScale(this->getScale());
	this->m_active_tentacle->setScale(this->getScale());
	for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++)
		(*it)->setScale(this->getScale());
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
			this->m_eyeRect = sf::IntRect(0, 0, 500, 500);
	} else {
		if (angle >= 90.0f && angle <= 270.0)
			range = angle - 90;
		else if (angle > 270.0f)
			range = 180 - (angle - 270);
		else
			range = 90 - angle;

		if (range < 22.0f)
			this->m_eyeRect = sf::IntRect(2500, 0, 500, 500);
		else if (range < 67.5f)
			this->m_eyeRect = sf::IntRect(2000, 0, 500, 500);
		else if (range < 112.5f)
			this->m_eyeRect = sf::IntRect(1500, 0, 500, 500);
		else if (range < 157.0f)
			this->m_eyeRect = sf::IntRect(1000, 0, 500, 500);
		else
			this->m_eyeRect = sf::IntRect(500, 0, 500, 500);
	}
	if (angle >= 270.0f || angle < 90.0f) {
		this->m_bodySprite.setTextureRect(bodyRect);
		this->m_eyeSprite.setTextureRect(eyeRect);
		//this->m_active_tentacle->setMirrored(false);
		//for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++)
			//(*it)->setMirrored(true);
	} else {
		this->m_bodySprite.setTextureRect(sf::IntRect(bodyRect.left + bodyRect.width, bodyRect.top, -bodyRect.width, bodyRect.height));
		this->m_eyeSprite.setTextureRect(sf::IntRect(eyeRect.left + eyeRect.width, eyeRect.top, -eyeRect.width, eyeRect.height));
		//this->m_active_tentacle->setMirrored(true);
		//for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++)
			//(*it)->setMirrored(false);
	}
	this->m_active_tentacle->setOrientation(angle);
	this->spreadTentacles();
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
		this->m_slimeRect = sf::IntRect(1000, 500, 500, 500);

		if (offset.x < 0)
			this->m_slimeSprite.setTextureRect(sf::IntRect(slimeRect.left + slimeRect.width, slimeRect.top, -slimeRect.width, slimeRect.height));
		else
			this->m_slimeSprite.setTextureRect(slimeRect);
	} else {
		this->m_slimeRect = sf::IntRect(500, 500, 500, 500);
		this->m_slimeSprite.setTextureRect(slimeRect);
	}
	this->setOrientation(angle * 180.0 / 3.141592653589793238463 + 180.0);

	this->m_active_tentacle->update(dt);
	for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++)
		(*it)->update(dt);
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);
	target.draw(this->m_slimeSprite, states);
	target.draw(this->m_bodySprite, states);
	target.draw(this->m_eyeSprite, states);
	this->m_active_tentacle->draw(target, states);
	for (auto it = this->m_passiveTentacles.begin(); it != this->m_passiveTentacles.end(); it++)
		(*it)->draw(target, states);
}

void Alien::initTentacle(Tentacle* tentacle, std::size_t index, sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
	tentacle->attach(this, texture);
	tentacle->setPosition(pos);
	tentacle->setScale(scale);
	tentacle->setTentacleIndex(index, this->m_passiveTentacles.size());
}

void Alien::spreadTentacles()
{
	std::size_t count = this->m_passiveTentacles.size();
	float increment = 1 / static_cast<float>(count + 1);
	float spread = 180.0f;
	float hspread = spread / 2;

	for (size_t i = 0; i < count; ++i) {
		float relAngle = (i + 1) * increment;
		float angleOffset = (2 * relAngle - 1) * hspread;
		float angle = this->getOrientation() + angleOffset;

		/*
		if (angleOffset < 0.0)
			angle = 360 + angleOffset;
		else
			angle = angleOffset;
			*/
		this->m_passiveTentacles[i]->setOrientation(angle);
	}
}
