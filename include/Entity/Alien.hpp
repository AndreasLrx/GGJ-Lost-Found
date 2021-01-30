/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** alien player class
*/

#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Entity/Entity.hpp"

class Alien : public Entity
{
public:
	Alien();
	~Alien();

    void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 }) override;
    void handleInput(sf::Event event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void onPositionChanged() override;
    void onScaleChanged() override;
    void onOrientationChanged() override;
private:
    sf::Sprite m_bodySprite;
    sf::Sprite m_eyeSprite;
};

#endif // !defined(ASTRONAUT_HPP)