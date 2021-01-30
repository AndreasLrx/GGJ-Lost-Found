/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** Settings
*/

#include "GameEngine/Settings.hpp"

void Settings::setWindSize(sf::Vector2u size)
{
    m_windSize = size;
    m_scale = size.x / 1280.f;
}

void Settings::setWindSize(unsigned int x, unsigned int y)
{
    setWindSize(sf::Vector2u(x, y));
}