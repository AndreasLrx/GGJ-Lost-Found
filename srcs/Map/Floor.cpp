/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Floor
*/

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Map/Floor.hpp"

Floor::Floor(GameDataRef data, Alien *alien)
{
    this->m_data = data;
    this->m_alien = alien;
    this->m_rooms = nullptr;
    this->floor_pos = {0, 0};
    this->set(std::string("1111111"), data);
}

void Floor::handleInput(sf::Event event)
{
    int doorUsed = -1;
    sf::Vector2f windSize(m_data->wind.getSize().x, m_data->wind.getSize().y);

    if (event.type != sf::Event::KeyPressed || event.key.code != sf::Keyboard::E)
        return;
    if (getDistSquared(m_alien->getPosition(), sf::Vector2f(windSize.x, windSize.y / 2.f)) < 20000) {
        if (floor_pos.x + 1 < (int)floor_map[floor_pos.y].size() && this->floor_map[floor_pos.y][floor_pos.x +1] != 'E') {
            doorUsed = Room::RIGHT;
        }
    } else if (getDistSquared(m_alien->getPosition(), sf::Vector2f(0, windSize.y / 2.f)) < 20000) {
        if (floor_pos.x -1 >= 0 && this->floor_map[floor_pos.y][floor_pos.x - 1] != 'E') {
            doorUsed = Room::LEFT; 
        }
    } else if (getDistSquared(m_alien->getPosition(), sf::Vector2f(windSize.x / 2.f, 0)) < 20000) {
        if (floor_pos.y - 1 >= 0 && this->floor_map[floor_pos.y - 1][floor_pos.x] != 'E') {
            doorUsed = Room::TOP;
        }
    } else if (getDistSquared(m_alien->getPosition(), sf::Vector2f(windSize.x / 2.f, windSize.y)) < 20000) {
        if (floor_pos.y + 1 < (int)floor_map.size() && this->floor_map[floor_pos.y + 1][floor_pos.x] != 'E') {
            doorUsed = Room::BOTTOM;
        }
    }
    if (doorUsed != -1)
        m_rooms[m_roomId].openDoor(doorUsed);
}

void Floor::change_room(float dt, std::string cur_room)
{
    sf::Vector2f windSize(m_data->wind.getSize().x, m_data->wind.getSize().y);

    (void)cur_room;
    m_cur_room->update(dt);
    int doorUsed = m_rooms[m_roomId].needChangeDoor();
    if (doorUsed != -1) {
        switch (doorUsed)
        {
        case Room::RIGHT:
            m_roomId++;
            floor_pos.x++;
            m_alien->setPosition(100, windSize.y / 2.f);
            break;
        case Room::LEFT:
            m_roomId--;
            floor_pos.x--;
            m_alien->setPosition(windSize.x - 100, windSize.y / 2.f);
            break;
        case Room::TOP:
            m_roomId -= floor_map[0].size();
            floor_pos.y--;
            m_alien->setPosition(windSize.x / 2.f, windSize.y - 100);
            break;
        case Room::BOTTOM:
            m_roomId += floor_map[0].size();
            floor_pos.y++;
            m_alien->setPosition(windSize.x / 2.f, 100);
            break;
        default:
            break;
        }
        m_cur_room = &m_rooms[m_roomId];
        m_cur_room->update(0);
    }
}

std::vector<std::string> floor_map_init(std::string str)
{
    std::stringstream str_buffer = (std::stringstream)str;
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(str_buffer, segment))
        seglist.push_back(segment);
    return (seglist);
}

void Floor::set(std::string cur_floor, GameDataRef data)
{
    sf::Vector2i pos(0, 0);
    (void)cur_floor;
    std::ifstream read_floor((std::string)"Level/Floor/floor_" + "1"); // Load the floor (level) you want. WIP
    std::stringstream floor_buffer;
    int size = 0; // number of room.
    int k = 0; // index to naviguate through room;
    floor_buffer << read_floor.rdbuf();  // idk
    this->floor_map = floor_map_init(floor_buffer.str()); // init string vector.
    for (unsigned long i = 0; i < floor_map.size(); i++) // compute size 
        size += floor_map[i].size();
    this->m_rooms = new Room[size]; // Allocate room
    this->m_floor_str = floor_buffer.str(); // Useless i think ?
    for (int index = 0; k < size; index++) { // For each room in the floor
        if (floor_buffer.str()[index] != '\n') { // If index of floor buffer is  a room
            if (floor_buffer.str()[index] != 'E') {
                std::ifstream read_room((std::string)"Level/Room/basic" + floor_buffer.str()[index]); // Load good room
                std::stringstream room_buffer;
                room_buffer << read_room.rdbuf();
                this->m_rooms[k].setAlien(m_alien);
                this->m_rooms[k].set(room_buffer.str(), data);
                this->m_rooms[k].initDoors(floor_map, pos);
            }
            pos.x++;
            k++;
        } else {
            pos.x = 0;
            pos.y++;
        }
    }
    m_roomId = 0;
    this->m_cur_room = &m_rooms[m_roomId];
}
