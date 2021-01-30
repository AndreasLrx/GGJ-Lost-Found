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

void Floor::set(std::string floor, GameDataRef data)
{
    std::ifstream t("file.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    this->m_room->set(buffer.str(), data);
}