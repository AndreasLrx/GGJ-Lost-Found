/*
**
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Circle
*/

#include <cmath>
#include "Circle.hpp"

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape circle = sf::CircleShape();

    circle.setPosition(this->m_pos);
    circle.setRadius(this->m_radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1);
    circle.setOrigin(this->m_radius, this->m_radius);
    target.draw(circle, states);
}

bool Circle::collidesWith(Circle other) const
{
    float dx = other.m_pos.x - this->m_pos.x;
    float dy = other.m_pos.y - this->m_pos.y;
    float radiusSum = this->m_radius + other.m_radius;

    return dx * dx + dy * dy <= radiusSum * radiusSum;
}
