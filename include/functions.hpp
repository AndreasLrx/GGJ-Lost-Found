/*
** EPITECH PROJECT, 2021
** GGJ Functions
** File description:
** Functions
*/

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <math.h>
#include <SFML/Graphics.hpp>

float getRand(float min, float max);
float getDist(sf::Vector2f posA, sf::Vector2f posB);
float getDistSquared(sf::Vector2f posA, sf::Vector2f posB);
float getLenSquared(sf::Vector2f vec);

inline float toDegrees(float radians)
{
    return radians * 180.0 / 3.141592653589793238463f;
}

inline float toRadians(float degrees)
{
    return degrees * (float)3.141592653589793238463f / 180.0;
}

#endif /* !FUNCTIONS_HPP_ */
