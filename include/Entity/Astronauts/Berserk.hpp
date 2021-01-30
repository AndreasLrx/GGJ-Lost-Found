/*
** EPITECH PROJECT, 2021
** GGJ Astronaut
** File description:
** berserk
*/

#ifndef ASTRONAUT_BERSERK_H
#define ASTRONAUT_BERSERK_H

#include "Entity/Astronauts/Astronaut.hpp"

class Berserk : public Astronaut
{
    public:
        Berserk() {};
        ~Berserk() {};

        void update(float dt);
};

#endif /* !ASTRONAUT_BERSERK_H */