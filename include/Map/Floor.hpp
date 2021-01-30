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
    Floor(GameDataRef data, Alien *alien);

    void set(std::string cur_room, GameDataRef data);
    void change_room(float dt, std::string cur_room);
    Room *get_room() {return (this->m_cur_room);};

    private:
        std::string m_floor_str;
        Room *m_cur_room;
        GameDataRef m_data;
        Alien *m_alien;
        Room *m_rooms;
};

#endif
