/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Floot
*/

#ifndef MAP_FLOOR_HPP
#define MAP_FLOOR_HPP

#include <string>
#include "GameEngine/Core.hpp"
#include "Map/Room.hpp"
class Room;

class Floor
{
    public:
    Floor(GameDataRef data);

    void set(std::string floor, GameDataRef data);
    Room *get_room() {return (this->m_room);};
    private:
        std::string m_floor_str;
        Room *m_room; // Change to arr when everything is good.
        GameDataRef m_data;
};

#endif
