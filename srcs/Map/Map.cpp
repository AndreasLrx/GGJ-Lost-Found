#include "Map/Room.hpp"
#include "Map/Tile.hpp"
#include "Map/Floor.hpp"
#include "Entity/Entity.hpp"
#include <string>
#include "GameEngine/Core.hpp"
#include <sstream>
#include <iostream>
#include <fstream>


static const unsigned int TILES_VERT = 18;
static const unsigned int TILES_HORZ = 32;
static const unsigned int TILES_PER_ROOM = TILES_HORZ * TILES_VERT - 1;
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
void Room::set(std::string str, GameDataRef data)
{
    sf::Vector2i cur_pos = {0, 0};

    sf::Texture *texture = data->assets.getTexture("TestTile_set");
    std::cout << "DEBUG\n";
    this->m_tiles = new Tile[TILES_PER_ROOM]; // init Tile array
    this->m_sprites.push_back(sf::Sprite(*texture, {0, 0, 50, 50}));

    this->m_data = data;
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        this->m_tiles[i].pos = {cur_pos.x, cur_pos.y};
        this->m_tiles[i].index = 0;
        cur_pos.x++;
        if (str[i] == '\n') {
            cur_pos.y++;
            cur_pos.x = 0;
        }
    }
}

Floor::Floor(GameDataRef data)
{
    this->m_data = data;
    this->m_room = new Room();
    this->set("1111111", data);
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i = 0; i != TILES_PER_ROOM; i++) {
        std::cout << m_sprites.size() << '\n';
        Tile &cur_tile = this->m_tiles[i];
        sf::Sprite sprite = this->m_sprites[cur_tile.index];
        sprite.setPosition({cur_tile.pos.x, cur_tile.pos.y});
        target.draw(sprite);
        cur_tile.index;
    }
}

void Floor::set(std::string floor, GameDataRef data)
{
    std::cout << "FLOOR SET";
    std::ifstream t("file.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    this->m_room->set(buffer.str(), data);
}
