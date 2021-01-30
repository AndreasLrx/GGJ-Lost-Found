/*
** EPITECH PROJECT, 2021
** GGJ Astronaut
** File description:
** Astronaut
*/

#ifndef ABSTRACT_ASTRONAUT_HPP
#define ABSTRACT_ASTRONAUT_HPP

#include <random>
#include "Entity/Entity.hpp"
#include "Entity/Alien.hpp"

class AbstractAstronaut : public Entity
{
    public:
        enum Types {SCIENTISTS, JETPACK, DISTANCE};

        virtual ~AbstractAstronaut() {};

        //virtual void initSprite(sf::Vector2f pos = sf::Vector2f(200, 200), sf::Vector2f scale = sf::Vector2f(50, 100)) = 0;
        
    protected:
        Alien *m_alien;
        int m_type;
};

#endif /* !ASTRONAUT_HPP */