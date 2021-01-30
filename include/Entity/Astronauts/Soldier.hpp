/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Soldier
*/

#ifndef ASTRONAUT_SOLDIER_H
#define ASTRONAUT_SOLDIER_H

#include "Entity/Astronauts/Astronaut.hpp"

class Soldier : public Astronaut
{
    public:
        Soldier() {};
        ~Soldier() {};

        void update(float dt);

    private:
};

#endif /* !ASTRONAUT_SOLDIER_H */