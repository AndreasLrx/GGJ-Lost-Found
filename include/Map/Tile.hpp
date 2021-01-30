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

        sf::Vector2i getPosition() {return sf::Vector2i(0, 0);};
        bool isWalkable() {return true;};
    
    private:
        Entity *m_entity;
        unsigned char m_type;
        sf::Vector2i pos;
};

#endif