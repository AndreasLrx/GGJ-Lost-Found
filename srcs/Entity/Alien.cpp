/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** alien player class
*/

#include <cmath>
#include "GameEngine/Core.hpp"
#include "Entity/Alien.hpp"

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
	this->m_bodySprite.setOrigin(242, 242);
	this->m_eyeSprite.setOrigin(242, 242);
	this->setPosition(pos);
	this->setScale(scale);
}

void Alien::handleInput(sf::Event event)
{
	if (event.type != sf::Event::EventType::KeyPressed)
		return;
	sf::Event::KeyEvent evt = event.key;
	switch (evt.code) {
	case sf::Keyboard::Z:
		this->move(0, 200);
		break;
	case sf::Keyboard::S:
		this->move(0, -200);
		break;
	case sf::Keyboard::Q:
		this->move(-200, 0);
		break;
	case sf::Keyboard::D:
		this->move(200, 0);
		break;
	}
}

void Alien::onPositionChanged()
{
	this->m_bodySprite.setPosition(this->getPosition());
	this->m_eyeSprite.setPosition(this->getPosition());
}

void Alien::onScaleChanged()
{
	this->m_bodySprite.setScale(this->getScale());
	this->m_eyeSprite.setScale(this->getScale());
}

void Alien::onOrientationChanged()
{
	sf::IntRect bodyRect = this->m_bodyRect;
	sf::IntRect eyeRect = this->m_eyeRect;
	float angle = this->getOrientation();
	float range;

	if (angle >= 90.0f && angle <= 270.0)
		range = angle - 90;
	else if (angle > 270.0f)
		range = 180 - (angle - 270);
	else
		range = 90 - angle;

	if (range < 36.0f)
		this->m_eyeRect = sf::IntRect(1936, 0, 484, 484);
	else if (range < 72.0f)
		this->m_eyeRect = sf::IntRect(968, 0, 484, 484);
	else if (range < 108.0f)
		this->m_eyeRect = sf::IntRect(0, 0, 484, 484);
	else if (range < 144.0f)
		this->m_eyeRect = sf::IntRect(484, 0, 484, 484);
	else
		this->m_eyeRect = sf::IntRect(2420, 0, 484, 484);

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
	sf::IntRect vp = this->m_gameData->wind.getViewport(this->m_gameData->wind.getDefaultView());
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(this->m_gameData->wind));
	sf::Vector2f lookVec = this->getPosition() - mousePos;
	float angle = atan2(lookVec.y, lookVec.x);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		offset.y -= 200 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		offset.x -= 200 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		offset.y += 200 * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		offset.x += 200 * dt;
	if (this->move(offset))
		this->m_bodyRect = sf::IntRect(484, 484, 484, 484);
	else
		this->m_bodyRect = sf::IntRect(0, 484, 484, 484);
	this->setOrientation(angle * 180.0 / 3.141592653589793238463 + 180.0);
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->m_bodySprite, states);
	target.draw(this->m_eyeSprite, states);
}
