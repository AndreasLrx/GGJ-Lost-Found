/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Room
*/

#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Tile;

class Room
{
    public:
        Room(std::string str);
        void drawRoom();

        Tile *getTile(sf::Vector2i pos) {return nullptr;};

    private:
        std::string m_room_str;
        Tile *m_Room_Entity;
};

#endif