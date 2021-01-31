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
#include "functions.hpp"

class Alien;

class AbstractAstronaut : public Entity
{
    public:
        enum Types {SCIENTISTS, JETPACK, DISTANCE};

        virtual ~AbstractAstronaut() {};
        
    protected:
        enum STATES {MOVE, IDLE, CAC, SHOOT, MOVE_SHOOT};
        sf::IntRect *m_animTextRectTabs[5];
        std::pair<float, int> m_animDatas[5];
        Alien *m_alien;
        int m_type;
        int m_state;
        float m_attackCooldown;
};

#endif /* !ASTRONAUT_HPP */
