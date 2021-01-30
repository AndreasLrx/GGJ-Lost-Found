/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Room
*/

#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "GameEngine/Core.hpp"

class Tile;

class Room : public sf::Drawable
{
    public:
        Room() {};
        void set(std::string str, GameDataRef data);
        void drawRoom();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Tile *getTile(sf::Vector2i pos) {if (pos.x || pos.y)return nullptr;};

    private:
        std::vector <sf::Sprite> m_sprites;
        std::string m_room_str;
        std::vector<std::vector<Tile *>> m_tilesVec;
        Tile *m_tiles;
        GameDataRef m_data;
};

#endif
