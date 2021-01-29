/*
** EPITECH PROJECT, 2021
** GGJ Astronaut
** File description:
** Astronaut
*/

#ifndef ASTRONAUT_HPP
#define ASTRONAUT_HPP

#include "Entity/Entity.hpp"

class Astronaut : public Entity
{
    public:
        enum Astronauts {SCIENTISTS, JETPACK, DISTANCE};

        Astronaut();
        virtual ~Astronaut();

        

    protected:
        int m_type;
};

#endif /* !ASTRONAUT_HPP */