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
	this->m_eyeSprite.setTexture(texture);
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

}

void Alien::onScaleChanged()
{

}

void Alien::onOrientationChanged()
{

}

void Alien::update(float dt)
{

}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	(void)target;
	(void)states;
}
