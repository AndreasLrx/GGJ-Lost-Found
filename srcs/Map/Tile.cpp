/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Tile
*/

#include "Map/Tile.hpp"

void Tile::init(Type type, sf::Vector2i pos, unsigned int index)
{
    m_type = type;
    m_pos = pos;
    m_index = index;
}