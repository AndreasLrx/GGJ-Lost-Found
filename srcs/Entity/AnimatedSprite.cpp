/*
** EPITECH PROJECT, 2021
** GGJ Animated Sprite
** File description:
** Animated Sprites
*/

#include <cmath>
#include "Entity/AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite()
{
	this->m_listener = [](auto sprite) {(void)sprite; };
}

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, std::size_t frameCount, sf::IntRect const frames[], float speed)
{
	this->m_inner = sf::Sprite();
	this->setTexture(texture, true);
	this->setTextureFrames(frameCount, frames);
	this->setAnimationSpeed(speed);
	this->m_listener = [](auto sprite) {(void)sprite; };
	this->update(0);
}

void AnimatedSprite::update(float dt)
{
	this->m_frame += dt * this->m_speed;
	if (this->m_frame < 0)
		this->m_frame = -this->m_frame;
	if (this->m_frame > this->m_frameMax)
		(this->m_listener)(*this);
	this->m_frame = std::fmod(this->m_frame, this->m_frameMax);

	sf::IntRect rect = this->m_frames[static_cast<std::size_t>(this->m_frame)];

	if (this->m_isMirrored)
		this->m_inner.setTextureRect(sf::IntRect(rect.left + rect.width, rect.top, -rect.width, rect.height));
	else
		this->m_inner.setTextureRect(rect);
	this->m_inner.setPosition(this->getPosition());
	this->m_inner.setRotation(this->getRotation());
	this->m_inner.setScale(this->getScale());
	this->m_inner.setOrigin(this->getOrigin());
}

void AnimatedSprite::setTexture(const sf::Texture& texture, bool resetFrames)
{
	if (resetFrames) {
		this->m_frames.clear();
		this->m_frame = 0.0f;
	}
	this->m_inner.setTexture(texture, resetFrames);
}

void AnimatedSprite::setTextureFrames(std::size_t frame_count, sf::IntRect const frames[])
{
	this->m_frames.clear();
	this->m_frameMax = (float)frame_count;
	if (frame_count == 0)
		return;
	this->m_frames.insert(this->m_frames.end(), &frames[0], &frames[frame_count]);
}

void AnimatedSprite::setAnimationSpeed(float speed)
{
	this->m_speed = speed;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
	return this->m_inner.getLocalBounds();
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
	return this->m_inner.getGlobalBounds();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->m_inner, states);
}
