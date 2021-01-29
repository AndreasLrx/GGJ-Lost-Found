/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Tile
*/

#ifndef MAP_TILE_HPP
#define MAP_TILE_HPP

#include <string>
#include "Entity/Entity.hpp"

class Tile
{
    public:
        Tile() {};
        Tile(unsigned char const type, sf::Vector2f vect);
    
    private:
        Entity *m_entity;
        unsigned char m_type;
};

#endif