/*
** EPITECH PROJECT, 2021
** alien
** File description:
** test
*/

#include "Entity/Test.hpp"

void Test::init(sf::Vector2f pos, sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(pos);
}

void Test::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}