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
#include "Entity/Test.hpp" // Remove after Entity.hpp work

struct Tile
{
    enum Type : char {EMPTY, OBSTACLE};
    Type type;
    sf::Vector2i pos;
    unsigned int index;
    bool isWalkable() {return (true);};
    sf::Vector2i getPosition() {sf::Vector2i vec{0, 0}; return (vec);};
/*    Tile() {};
    Tile(unsigned char const type, sf::Vector2i pos);

    void set(unsigned char const type, sf::Vector2i pos, sf::Texture *texture);
    sf::Vector2i getPosition() {return sf::Vector2i{0, 0};};
    bool isWalkable() {return true;};
    Test *m_entity; // Change to Entity after Entity.hpp is functionnal
private:
    unsigned char m_type; // Type of the block
    sf::Vector2i pos;
*/
};

#endif
