/*
** EPITECH PROJECT, 2021
** GGJ Alien
** File description:
** An Alien's ranged tentacle
*/

#ifndef RANGED_TENTACLE_HPP
#define RANGED_TENTACLE_HPP

#include "Entity/Tentacles/Tentacle.hpp"

class Alien;

class RangedTentacle : public Tentacle
{
public:
    RangedTentacle();

    virtual void attack() override;
};

#endif // !defined(RANGED_TENTACLE_HPP)
