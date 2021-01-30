/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Room
*/

#include "Map/Room.hpp"

static const unsigned int TILES_VERT = 18;
static const unsigned int TILES_HORZ = 32;
static const unsigned int TILES_PER_ROOM = TILES_HORZ * TILES_VERT - 1;

void Room::set(std::string str, GameDataRef data)
{
    sf::Vector2i cur_pos = {0, 0};
    sf::Texture *texture = data->assets.getTexture("TestTile_Set");
    Tile *currTile;
    m_tileSize = 128;

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
        currTile->init(static_cast<Tile::Type>(str[i] - '0'), cur_pos, static_cast<unsigned int>(str[i] - '0'));
        this->m_tilesVec[cur_pos.y].push_back(currTile);
        cur_pos.x++;
    }
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    Tile *current;
    sf::Vector2i tilePos;

    for (size_t y = 0; y < m_tilesVec.size(); y++) {
        for (size_t x = 0; x < m_tilesVec[y].size(); x++) {
            current = this->m_tilesVec[y][x];
            tilePos = current->getPosition();
            sprite = this->m_sprites[current->getIndex()];
            sprite.setPosition(sf::Vector2f(tilePos.x * m_tileSize, tilePos.y * m_tileSize));
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

Tile *Room::getTile(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= static_cast<int>(m_tilesVec.size()) || pos.x >= static_cast<int>(m_tilesVec[0].size()))
        return nullptr;
    return m_tilesVec[pos.y][pos.x];
}

Tile *Room::getTileAt(sf::Vector2f pos)
{
    sf::Vector2i posTile(pos.x / m_tileSize, pos.y / m_tileSize);
    return getTile(posTile);
}