/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Shooter
*/

#ifndef ASTRONAUT_SHOOTER_H
#define ASTRONAUT_SHOOTER_H

#include "Entity/Astronauts/Astronaut.hpp"

class Shooter : public Astronaut
{
    public:
        Shooter() {};
        ~Shooter() {};

        void update(float dt);

    private:
};

#endif /* !ASTRONAUT_SHOOTER_H */