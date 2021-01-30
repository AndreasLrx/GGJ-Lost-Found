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

float getDist(sf::Vector2f posA, sf::Vector2f posB);
float getDistSquared(sf::Vector2f posA, sf::Vector2f posB);
float getLenSquared(sf::Vector2f vec);

float getRand(float min, float max);

#endif /* !FUNCTIONS_HPP_ */