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
        Scientist();
        ~Scientist();

        void init();
        void handleInput(sf::Event event);
        void update(float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);

        int isAlive();

    private:
        
};

#endif /* !ASTRONAUTS_SCIENTISTS_H */