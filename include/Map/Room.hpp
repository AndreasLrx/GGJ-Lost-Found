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
#include "Entity/Alien.hpp"
#include "GameEngine/Core.hpp"
#include "Map/Tile.hpp"

class Tile;
class Astronaut;

class Room : public sf::Drawable
{
    public:
        Room() {};
        ~Room() {};
        void setAlien(Alien *alien) {m_alien = alien;};
        sf::Vector2f getEmptyPos();
        void set(std::string str, GameDataRef data);
        void drawRoom();

        void initDoors(std::vector<std::string> mapStr, sf::Vector2i pos);

        void update(float dt);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Tile *getTileAt(sf::Vector2f pos);
        Tile *getTile(sf::Vector2i pos);
        sf::Vector2f getRealTilePos(sf::Vector2i tilePos);
        unsigned int getTileSize() {return m_tileSize;};

    private:
        enum DOORS{LEFT = 2, TOP = 3, RIGHT = 0, BOTTOM = 1};
        char type;
        sf::Sprite m_door;
        std::vector <sf::Sprite> m_sprites;
        std::string m_room_str;
        std::vector<std::vector<Tile *>> m_tilesVec;
        sf::Sprite background;
        Tile *m_tiles;
        GameDataRef m_data;
        unsigned int m_tileSize;

        Alien *m_alien;
        std::vector<Astronaut *> m_astronauts;
        int m_doors[4];
};

#endif
