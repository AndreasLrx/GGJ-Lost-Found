/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Scientis
*/

#ifndef ASTRONAUTS_SCIENTISTS_H
#define ASTRONAUTS_SCIENTISTS_H

#include "Entity/Astronauts/Astronaut.hpp"

class Scientist : public Astronaut
{
    public:
        Scientist() {};
        ~Scientist() {};

        void setAnimationListener();
        void update(float dt);
    private:
        
};

#endif /* !ASTRONAUTS_SCIENTISTS_H */