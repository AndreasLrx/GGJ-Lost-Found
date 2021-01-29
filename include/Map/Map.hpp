#ifndef __MAP__
#define __MAP__

#include "Entity/Entity.hpp"
#include <string>

class Tile
{
public:
    Tile() {};
    Tile(unsigned char const type, sf::Vector2f vect);
    Entity *m_entity;
    unsigned char m_type;
};

class Room
{
public:
    std::string m_room_str;
    Room(std::string str);
    void drawRoom();
    Tile *m_Room_Entity;
};

class Floor
{
public:
    std::string m_floor_str;
    Room *m_room;
    void Floor_init();
};
#endif
