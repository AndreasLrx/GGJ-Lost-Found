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

class Tile
{
    public:
        enum Type : char {EMPTY, OBSTACLE};
        Tile() {};
        ~Tile() {};

        void init(Type type, sf::Vector2i pos, unsigned int index);
        bool isWalkable() {return m_type == EMPTY;};

        Type getType() {return m_type;};
       sf::Vector2i getPosition() {return m_pos;};
        unsigned int getIndex() {return m_index;};

    private:
        Type m_type;
        sf::Vector2i m_pos;
        unsigned int m_index;
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
