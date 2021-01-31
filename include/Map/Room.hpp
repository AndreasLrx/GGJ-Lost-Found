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
#include "Entity/Projectiles/AbstractProjectile.hpp"
#include "Map/Tile.hpp"
#include "Entity/AnimatedSprite.hpp"

class Tile;
class Astronaut;

class Room : public sf::Drawable
{
    public:
        enum DOORS{LEFT = 2, TOP = 3, RIGHT = 0, BOTTOM = 1};

        Room() {m_hasJar = false;m_doorTimer = -1; m_doorAnimated = -1;};
        ~Room() {};
        void setAlien(Alien *alien) {m_alien = alien;};
        sf::Vector2f getEmptyPos();
        void set(std::string str, GameDataRef data);
        void drawRoom();

        void initDoors(std::vector<std::string> mapStr, sf::Vector2i pos);
        void openDoor(int door);
        int needChangeDoor();
        int hasEnnemys() {return !m_astronauts.empty();};

        void update(float dt);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Tile *getTileAt(sf::Vector2f pos);
        Tile *getTile(sf::Vector2i pos);
        sf::Vector2f getRealTilePos(sf::Vector2i tilePos);
        unsigned int getTileSize() {return m_tileSize;};
        GameDataRef getGameData();

        void spawnProjectile(AbstractProjectile* projectile, Entity* owner);

        std::vector<Astronaut*>& getAstronauts();

    private:
        void initJar(char jar);
    
        char type;
        sf::Sprite m_door;
        std::vector <sf::Sprite> m_sprites;
        std::string m_room_str;
        std::vector<std::vector<Tile *>> m_tilesVec;
        sf::Sprite background;
        GameDataRef m_data;
        unsigned int m_tileSize;

        Alien *m_alien;
        std::vector<Astronaut *> m_astronauts;
        std::vector<AbstractProjectile*> m_projectiles;
        int m_doors[4];
        bool m_hasJar;
        AnimatedSprite m_tentacleJar;
        AnimatedSprite m_animatedDoor;
        float m_doorTimer;
        int m_doorAnimated;
};

inline GameDataRef Room::getGameData()
{
    return this->m_data;
}

inline std::vector<Astronaut *>& Room::getAstronauts()
{
    return this->m_astronauts;
}

#endif
