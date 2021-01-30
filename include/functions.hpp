/*
** EPITECH PROJECT, 2021
** GGJ 
** File description:
** 
*/

#ifndef _HPP_
#define _HPP_

#include <math.h>
#include <SFML/Graphics.hpp>

float getDist(sf::Vector2f posA, sf::Vector2f posB);
float getDistSquared(sf::Vector2f posA, sf::Vector2f posB);
float getLenSquared(sf::Vector2f vec);

inline float toDegrees(float radians)
{
    return radians * 180.0 / 3.141592653589793238463;
}

inline float toRadians(float degrees)
{
    return degrees * 3.141592653589793238463 / 180.0;
}

#endif /* !_HPP_ */