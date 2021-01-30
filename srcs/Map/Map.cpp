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
    sf::Texture *texture = data->assets.getTexture("TestTile_Set");
    Tile *currTile;

    this->m_tiles = new Tile[TILES_PER_ROOM]; // init Tile array
    this->m_sprites.push_back(sf::Sprite(*texture, {0, 0, 128, 128}));
    this->m_sprites.push_back(sf::Sprite(*texture, {512, 0, 128, 128}));

    this->m_data = data;
    this->m_tilesVec.push_back(std::vector<Tile *>());
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cur_pos.y++;
            cur_pos.x = 0;
            m_tilesVec.push_back(std::vector<Tile *>());
            continue;
        }
        currTile = new Tile;
        currTile->pos = cur_pos;
        currTile->index = static_cast<unsigned int>(str[i] - '0');
        currTile->type = static_cast<Tile::Type>(str[i] - '0');
        this->m_tilesVec[cur_pos.y].push_back(currTile);
        cur_pos.x++;
    }
}

Floor::Floor(GameDataRef data)
{
    this->m_data = data;
    this->m_room = new Room();
    this->set(std::string("1111111"), data);
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t y = 0; y < m_tilesVec.size(); y++) {
        for (size_t x = 0; x < m_tilesVec[y].size(); x++) {
            Tile *cur_tile = this->m_tilesVec[y][x];
            sf::Sprite sprite = this->m_sprites[cur_tile->index];
            sprite.setPosition(static_cast<int>(cur_tile->pos.x * 128), static_cast<int>(cur_tile->pos.y * 128));
            target.draw(sprite, states);
        }
    }
    /*for(unsigned int i = 0; i != TILES_PER_ROOM; i++) {
        std::cout << m_sprites.size() << '\n';
        Tile &cur_tile = this->m_tiles[i];
        sf::Sprite sprite = this->m_sprites[cur_tile.index];
        sprite.setPosition({cur_tile.pos.x, cur_tile.pos.y});
        target.draw(sprite, states);
        cur_tile.index;
    }*/
}

void Floor::set(std::string floor, GameDataRef data)
{
    std::ifstream t("file.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    this->m_room->set(buffer.str(), data);
}
