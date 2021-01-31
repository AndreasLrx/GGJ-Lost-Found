/*
**
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Circle
*/

#include <SFML/Graphics.hpp>

class Circle : public sf::Drawable
{
public:
    sf::Vector2f m_pos;
    float m_radius;

    Circle(sf::Vector2f pos = { 0.0f, 0.0f }, float radius = 1.0f): m_pos(pos), m_radius(radius)
    {};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool collidesWith(Circle other) const;
};
