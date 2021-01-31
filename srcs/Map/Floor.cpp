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

/*
Tile::Tile(unsigned char const type, sf::Vector2i pos)
{
    this->m_entity->setPosition(pos.y, pos.y);
    this->m_type = type;
}

void Tile::set(unsigned char const type, sf::Vector2i vect, sf::Texture *texture)
{
    sf::Vector2f true_vect = {(float)vect.x, (float)vect.y};

    this->m_type = type;
    this->m_entity->init(true_vect, texture);
}
*/

Floor::Floor(GameDataRef data, Alien *alien)
{
    this->m_data = data;
    this->m_alien = alien;
    this->m_rooms = nullptr;
    this->floor_pos = {0, 0};
    this->set(std::string("1111111"), data);
}

void Floor::change_room(float dt, std::string cur_room)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && floor_pos.y - 1 >= 0)
        if (this->floor_map[floor_pos.y - 1][floor_pos.x] != '.') {
            std::cout<<"up"<<std::endl;
            floor_pos.y--;
            m_roomId -= floor_map[0].size();
            //this->m_cur_room -= floor_map.size();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && floor_pos.y + 1 < (int)floor_map.size()) {
        if (this->floor_map[floor_pos.y + 1][floor_pos.x] != '.') {
            std::cout<<"Down"<<std::endl;
            m_roomId += floor_map[0].size();
            //this->m_cur_room += floor_map.size();
            this->floor_pos.y++;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && floor_pos.x -1 >= 0)
        if (this->floor_map[floor_pos.y][floor_pos.x - 1] != '.'){
            std::cout<<"Left"<<std::endl;
            m_roomId -= 1;
            //this->m_cur_room--;
            floor_pos.x--;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && floor_pos.x + 1 < (int)floor_map[floor_pos.y].size())
        if (this->floor_map[floor_pos.y][floor_pos.x +1] != '.') {
            std::cout<<"Right"<<std::endl;
            m_roomId += 1;
            //this->m_cur_room++;
            floor_pos.x++;
        }
    m_cur_room = &m_rooms[m_roomId];
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (int i = 0; i < (int)this->floor_map.size(); i++) {
            std::cout << floor_map[i] << " :  " << &m_rooms[i * 3 + 0] << ",  " << &m_rooms[i * 3 + 1] << ",  " << &m_rooms[i * 3 + 2] <<'\n';
        }
        std::cout<<"Map size = "<<floor_map.size()<<std::endl;
        std::cout << floor_pos.x << '.' << floor_pos.y << " <=> "<<floor_pos.x + floor_map.size() * floor_pos.y<<" : " << this->m_cur_room << "\n\n\n";
    }
    m_cur_room->update(dt);
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
    for (int index = 0; index < size; index++) { // For each room in the floor
        if (floor_buffer.str()[index] != '\n') { // If index of floor buffer is  a room
            std::cout << "Character : " << floor_buffer.str()[index] << " go with the room :" << k << " at address : " << &this->m_rooms[k] <<  '\n';
            std::ifstream read_room((std::string)"Level/Room/basic" + floor_buffer.str()[index]); // Load good room
            std::stringstream room_buffer;
            room_buffer << read_room.rdbuf();
            this->m_rooms[k].setAlien(m_alien);
            this->m_rooms[k].set(room_buffer.str(), data);
            k++;
        }
    }
    for (int i = 0; i < k; i++) {
        std::cout<<"Room "<<i<<" = "<<&this->m_rooms[i]<<std::endl;;
    }
    m_roomId = 0;
    this->m_cur_room = &m_rooms[m_roomId];
}
