/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** alien player class
*/

#include "Entity/Alien.hpp"

Alien::Alien() {}

Alien::~Alien() {}

void Alien::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
	this->m_bodySprite.setTexture(texture);
	this->m_bodySprite.setTextureRect(sf::IntRect(0, 484, 484, 484));
	this->m_eyeSprite.setTexture(texture);
	this->m_eyeSprite.setTextureRect(sf::IntRect(0, 0, 484, 484));
	this->setPosition(pos);
	this->setScale(scale);
}

void Alien::handleInput(sf::Event event)
{
/*	if (event.type != sf::Event::EventType::KeyPressed)
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
		this->move(-10, 0);
		break;
	case sf::Keyboard::D:
		this->move(200, 0);
		break;
	}*/
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

void Alien::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        this->move(0, -200 * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        this->move(-200 * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->move(0, 200 * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->move(200 * dt, 0);
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->m_bodySprite, states);
	target.draw(this->m_eyeSprite, states);
}
