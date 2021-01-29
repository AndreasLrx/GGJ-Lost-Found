/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Floot
*/

#ifndef MAP_FLOOR_HPP
#define MAP_FLOOR_HPP

#include <string>

class Room;

class Floor
{
    public:
        void Floor_init();

    private:
        std::string m_floor_str;
        Room *m_room;
};

#endif