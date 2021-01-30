/*
** EPITECH PROJECT, 2021
** GGJ 
** File description:
** Useful functions
*/

#include "functions.hpp"

float getLenSquared(sf::Vector2f vec)
{
    return powf(vec.x, 2) + powf(vec.y, 2);
}

float getDist(sf::Vector2f posA, sf::Vector2f posB)
{
    return sqrt(getDistSquared(posA, posB));
}

float getDistSquared(sf::Vector2f posA, sf::Vector2f posB)
{
    return getLenSquared(posA - posB);
}