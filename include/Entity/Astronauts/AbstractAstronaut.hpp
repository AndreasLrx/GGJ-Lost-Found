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

class Alien;

class AbstractAstronaut : public Entity
{
    public:
        enum Types {SCIENTISTS, JETPACK, DISTANCE};

        virtual ~AbstractAstronaut() {};
        
    protected:
        Alien *m_alien;
        int m_type;
};

#endif /* !ASTRONAUT_HPP */