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

void Room::initJar(char jar)
{
    m_hasJar = true;
    sf::FloatRect bounds;
    sf::IntRect rect[] = {{0, 0, 716, 1215}, {716, 0, 716, 1215}, {1432, 0, 716, 1215}, {2148, 0, 716, 1215}, {2864, 0, 716, 1215}, {3580, 0, 716, 1215}};
    switch (jar) {
    case 'A':
        this->m_tentacleJar.setTexture(*m_data->assets.getTexture("armored_jar"));
        this->m_tentacleJar.setAnimationSpeed(2.f);
        break;
    case 'S':
        this->m_tentacleJar.setTexture(*m_data->assets.getTexture("shot_jar"));
        this->m_tentacleJar.setAnimationSpeed(2.5f);
        break;
    case 'V':
        this->m_tentacleJar.setTexture(*m_data->assets.getTexture("vanilla_jar"));
        this->m_tentacleJar.setAnimationSpeed(3.5f);
        break;
    default:
        m_hasJar = false;
        return;
    }
    this->m_tentacleJar.setScale(sf::Vector2f(0.25, 0.25));
    this->m_tentacleJar.setTextureFrames(6, rect);
    m_tentacleJar.update(0);
    bounds = m_tentacleJar.getLocalBounds();
    this->m_tentacleJar.setOrigin(bounds.width / 2.f, bounds.height);
    this->m_tentacleJar.setPosition(sf::Vector2f(640, 500));
}

void Room::set(std::string str, GameDataRef data)
{
    sf::Vector2i cur_pos = {0, 0};
    sf::Texture *texture = data->assets.getTexture("TestTile_Set");
    Tile *currTile;

    m_tileSize = 55;
    this->m_door = sf::Sprite(*data->assets.getTexture("doors"));
    this->m_door.setTextureRect(sf::IntRect(0, 0, 171, 293));
    this->m_sprites.push_back(sf::Sprite(*texture, {0, 0, 55, 55}));
    this->m_sprites.push_back(sf::Sprite(*texture, {55, 0, 55, 55}));
    this->background = sf::Sprite(*data->assets.getTexture("bg"));
    this->m_data = data;
    this->m_tilesVec.push_back(std::vector<Tile *>());
    m_astronauts.clear();
    if (str[0] == 'S' || str[0] == 'A' || str[0] == 'V') {
        initJar(str[0]);
        str[0] = '0';
    }
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
    if (m_hasJar)
        return;
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
    this->m_alien->setRoom(this);
    for (size_t i = 0; i < m_astronauts.size(); i++)
        m_astronauts[i]->update(dt);
    if (m_hasJar)
        m_tentacleJar.update(dt);
    if (m_doorAnimated >= 0) {
        if (m_doorTimer < 0)
            m_animatedDoor.update(dt);
    }
    for (auto it = this->m_projectiles.begin(); it < this->m_projectiles.end(); ++it) {
        if (!(*it)->isAlive()) {
            delete (*it);
            it = this->m_projectiles.erase(it);
            if (it >= this->m_projectiles.end())
                break;
        } else {
            (*it)->update(dt);
        }
    }
}

int Room::needChangeDoor()
{
    int door = -1;

    if (m_doorAnimated >= 0 && m_doorTimer >= 0) {
        door = m_doorAnimated;
        m_doorAnimated = -1;
        m_doorTimer = -1;
    }
    return door;
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
        if (i == RIGHT) {
            s_door.setRotation(0);
            s_door.setPosition(sf::Vector2f(1200, 300));
        }
        if (i == BOTTOM) {
            s_door.setRotation(90);
            s_door.setPosition(sf::Vector2f(700, 650));
        }
        if (i == LEFT) {
            s_door.setRotation(180);
            s_door.setPosition(sf::Vector2f(80, 400));
        }
        if (i == TOP) {
            s_door.setRotation(270);
            s_door.setPosition(sf::Vector2f(600, 80));
        }
        if (m_doors[i]) {
            if (m_doorAnimated >= 0 && static_cast<unsigned int>(m_doorAnimated) == i)
                target.draw(m_animatedDoor);
            else
                target.draw(s_door, states);
        }
            
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
    if (m_hasJar)
        target.draw(m_tentacleJar);
    for (size_t i = 0; i < m_astronauts.size(); i++)
        target.draw(*m_astronauts[i]);
    for (auto it = this->m_projectiles.begin(); it < this->m_projectiles.end(); ++it)
        target.draw(**it);
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

void Room::initDoors(std::vector<std::string> mapStr, sf::Vector2i pos)
{
    sf::IntRect frames[] = {{0, 0, 171, 293}, {171, 0, 171, 293}, {342, 0, 171, 293}, {513, 0, 171, 293}, {684, 0, 171, 293}};
    sf::Vector2i size(mapStr[0].size(), mapStr.size());

    m_doors[LEFT] = !(pos.x == 0 || mapStr[pos.y][pos.x - 1] == 'E'); // Left
    m_doors[TOP] = !(pos.y == 0 || mapStr[pos.y - 1][pos.x] == 'E'); // Top
    m_doors[RIGHT] = !(pos.x + 1 >= size.x || mapStr[pos.y][pos.x + 1] == 'E'); // Right
    m_doors[BOTTOM] = !(pos.y + 1 >= size.y || mapStr[pos.y + 1][pos.x] == 'E'); // Bottom
    m_animatedDoor.setAnimationSpeed(6.f);
    m_animatedDoor.setTexture(*m_data->assets.getTexture("doors"));
    m_animatedDoor.setTextureFrames(5, frames);
    m_animatedDoor.setScale(0.4f, 0.4f);
    m_animatedDoor.setAnimationEndListener([=](auto sprite){
        (void)sprite;
        m_doorTimer = 0.1f;
    });
}

void Room::openDoor(int door)
{
    m_doorAnimated = door;
    switch (door) {
    case LEFT:
        m_animatedDoor.setRotation(180);
        m_animatedDoor.setPosition(sf::Vector2f(80, 400));
        break;
    case RIGHT:
        m_animatedDoor.setRotation(0);
        m_animatedDoor.setPosition(sf::Vector2f(1200, 300));
        break;
    case TOP:
        m_animatedDoor.setRotation(270);
        m_animatedDoor.setPosition(sf::Vector2f(600, 80));
        break;
    case BOTTOM:
        m_animatedDoor.setRotation(90);
        m_animatedDoor.setPosition(sf::Vector2f(700, 650));
        break;
    default:
        break;
    }
}

void Room::spawnProjectile(AbstractProjectile* projectile, Entity* owner)
{
    this->m_projectiles.push_back(projectile);
    projectile->spawn(owner, this);
}
