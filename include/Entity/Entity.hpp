/*
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
    public:
        Entity();
        virtual ~Entity();

        virtual void init();
        virtual void handleInput(sf::Event event);
        virtual void update(float dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
};

#endif /* !ENTITY_HPP */