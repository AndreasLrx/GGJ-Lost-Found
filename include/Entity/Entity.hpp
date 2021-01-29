/*
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Room;

class Entity : public sf::Drawable
{
    public:
        virtual ~Entity() {};

        virtual void init() = 0;
        virtual void handleInput(sf::Event event) = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        virtual sf::Vector2f getPosition() = 0;
        virtual void setPosition(sf::Vector2f pos) = 0;
        virtual void setPosition(float x, float y) = 0;

        virtual int isAlive() = 0;

    protected:
        bool m_isAlive;
        Room *m_room;
};

#endif /* !ENTITY_HPP */