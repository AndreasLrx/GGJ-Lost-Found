/*
** EPITECH PROJECT, 2021
** GGJ Map
** File description:
** Room
*/

#include "Map/Room.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "States/GameState.hpp"
#include "iostream"

sf::Vector2f Room::getEmptyPos()
{
    int tries = 0;
    int empty = 0;
    sf::Vector2i mapSize(m_tilesVec[0].size(), m_tilesVec.size());
    sf::Vector2i pos(static_cast<int>(getRand(0, mapSize.x)), static_cast<int>(getRand(0, mapSize.y)));

    empty = getTile(pos)->isWalkable();
    while (tries < 100 && !empty) {
        pos = sf::Vector2i(static_cast<int>(getRand(0, mapSize.x)), static_cast<int>(getRand(0, mapSize.y)));
        tries++;
    }
    if (tries >= 100)
        return sf::Vector2f(-1, -1);
    return getRealTilePos(pos);
}

void Room::set(std::string str, GameDataRef data)
{
    sf::Vector2i cur_pos = {0, 0};
    sf::Texture *texture = data->assets.getTexture("TestTile_Set");
    Tile *currTile;
    m_tileSize = 55;
    this->m_door = sf::Sprite(*data->assets.getTexture("door"));
    this->m_sprites.push_back(sf::Sprite(*texture, {0, 0, 55, 55}));
    this->m_sprites.push_back(sf::Sprite(*texture, {55, 0, 55, 55}));
    this->background = sf::Sprite(*data->assets.getTexture("bg"));
    this->m_data = data;
    this->m_tilesVec.push_back(std::vector<Tile *>());
    m_astronauts.clear();
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
    sf::Vector2f pos;
    for (int i = 0; i < 1; i++) {
        pos = getEmptyPos();
        if (pos.x < 0)
            continue;
        Scientist *sci = new Scientist();
        sci->init(*m_data->assets.getTexture("scientist"), pos, sf::Vector2f(0.35f, 0.35f));
        sci->setAlien(m_alien);
        sci->setRoom(this);
        m_astronauts.push_back(sci);
    }
    for (int i = 0; i < 1; i++) {
        pos = getEmptyPos();
        if (pos.x < 0)
            continue;
        Soldier *sho = new Soldier();
        sho->init(*m_data->assets.getTexture("soldier"), pos, sf::Vector2f(0.35f, 0.35f));
        sho->setAlien(m_alien);
        sho->setRoom(this);
        m_astronauts.push_back(sho);
    }
    for (int i = 0; i < 1; i++) {
        pos = getEmptyPos();
        if (pos.x < 0)
            continue;
        Berserk *bers = new Berserk();
        bers->init(*m_data->assets.getTexture("berserk"), pos, sf::Vector2f(0.35f, 0.35f));
        bers->setAlien(m_alien);
        bers->setRoom(this);
        m_astronauts.push_back(bers);
    }
}

void Room::update(float dt)
{
    for (size_t i = 0; i < m_astronauts.size(); i++)
        m_astronauts[i]->update(dt);
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sf::Sprite s_door;
    Tile *current;
    sf::Vector2i tilePos;

    target.draw(background, states);
    for (unsigned int i = 0; i != 4; i++) {
        s_door = this->m_door;
        s_door.setScale(sf::Vector2f(0.4, 0.4));
        if (i == 0) {
            s_door.setRotation(0);
            s_door.setPosition(sf::Vector2f(1200, 300));
        }
        if (i == 1) {
            s_door.setRotation(90);
            s_door.setPosition(sf::Vector2f(700, 650));
        }
        if (i == 2) {
            s_door.setRotation(180);
            s_door.setPosition(sf::Vector2f(80, 400));
        }
        if (i == 3) {
            s_door.setRotation(270);
            s_door.setPosition(sf::Vector2f(600, 80));
        }
        target.draw(s_door, states);
    }
    for (size_t y = 0; y < m_tilesVec.size(); y++) {
        for (size_t x = 0; x < m_tilesVec[y].size(); x++) {
            current = this->m_tilesVec[y][x];
            tilePos = current->getPosition();
            sprite = this->m_sprites[current->getIndex()];
            sprite.setPosition(sf::Vector2f(tilePos.x * m_tileSize + 91, tilePos.y * m_tileSize + 90));
            target.draw(sprite, states);
        }
    }
    for (size_t i = 0; i < m_astronauts.size(); i++)
        target.draw(*m_astronauts[i]);
}

Tile *Room::getTile(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= static_cast<int>(m_tilesVec.size()) || pos.x >= static_cast<int>(m_tilesVec[0].size()))
        return nullptr;
    return m_tilesVec[pos.y][pos.x];
}

Tile *Room::getTileAt(sf::Vector2f pos)
{
    sf::Vector2i posTile((pos.x - 91)/ m_tileSize, (pos.y - 90) / m_tileSize);
    return getTile(posTile);
}

sf::Vector2f Room::getRealTilePos(sf::Vector2i tilePos)
{
    return sf::Vector2f(tilePos.x * m_tileSize + 91, tilePos.y * m_tileSize + 90);
}
