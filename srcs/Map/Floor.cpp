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

Floor::Floor(GameDataRef data)
{
    this->m_data = data;
    this->m_room = new Room();
    this->set(std::string("1111111"), data);
}

void Floor::change_room(std::string cur_room)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        this->m_cur_room++;
    }
}

void Floor::set(std::string cur_floor, GameDataRef data)
{
    std::ifstream read_floor((std::string)"Level/Floor/floor_" + "1");
    std::stringstream floor_buffer;
    floor_buffer << read_floor.rdbuf();
    this->m_room = new Room[floor_buffer.str().size()];
    for (unsigned int i = 0; i < cur_floor.size(); i++) {
        std::ifstream read_room((std::string)"Level/Room/basic" + floor_buffer.str()[i]);
        std::stringstream room_buffer;
        room_buffer << read_room.rdbuf();
        this->m_room[i].set(room_buffer.str(), data);
    }
    this->m_cur_room = &m_room[0];
}
