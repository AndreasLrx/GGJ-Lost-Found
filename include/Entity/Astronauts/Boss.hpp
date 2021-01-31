/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Boss
*/

#ifndef ASTRONAUTS_BOSS_H
#define ASTRONAUTS_BOSS_H

#include "Entity/Astronauts/Soldier.hpp"

class Boss : public Soldier
{
    public:
        Boss() {m_lifes = 5;};
        ~Boss() {};

        virtual void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });


        void update(float dt);

        void takeDamage();

    protected:
    private:
        int m_lifes;
};

#endif /* !ASTRONAUTS_BOSS_H */