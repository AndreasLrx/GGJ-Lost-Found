/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Astronaut
*/

#include <iostream>
#include "Entity/Astronauts/Astronaut.hpp"
#include "Entity/Alien.hpp"
#include "functions.hpp"

Astronaut::Astronaut()
{
    m_pathUpdateTimer = 5;
    this->setOrientation(0);
}

Astronaut::~Astronaut()
{

}

void Astronaut::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::FloatRect bounds;
	sf::IntRect frames[] = { {0, 0, 250, 250}, {250, 0, 250, 250}, {500, 0, 250, 250}, {750, 0, 250, 250}};

    m_move = sf::Vector2f(0, 0);
    m_running = 0;
    this->m_sprite.setTexture(texture);
    this->m_sprite.setPosition(pos);
    this->m_sprite.setScale(scale);
    this->m_sprite.setTextureFrames(4, frames);
    this->m_sprite.setAnimationSpeed(6.f);
    this->setPosition(pos);
    this->setScale(scale);
    m_sprite.update(0);
    bounds = m_sprite.getLocalBounds();
    this->m_sprite.setOrigin(bounds.width / 2.f, bounds.height);
}

void Astronaut::setAlien(Alien *alien)
{
    m_alien = alien;
}

void Astronaut::setRoom(Room *room)
{
    m_room = room;
}

void Astronaut::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
        return;
}

void Astronaut::onPositionChanged()
{
	this->m_sprite.setPosition(this->getPosition());
}

void Astronaut::update(float dt)
{
    if (dt)
        return;
}

void Astronaut::updatePathTimer(float dt)
{
    if (m_pathUpdateTimer >= 0.5) {
        m_pathUpdateTimer = 0;
        if (!m_running)
            resetPath(m_alien->getPosition());
        else
            runAway(m_alien->getPosition());
    }
    m_pathUpdateTimer += dt;
    this->m_sprite.update(dt);
}

void Astronaut::moveToPath(float speed, float dt)
{
    if (m_path.size() != 0) {
        unsigned int tileSize = m_room->getTileSize();
        sf::Vector2f tilePos = m_room->getRealTilePos(m_path[m_path.size() - 1]) + sf::Vector2f(tileSize * getRand(0, 1.f), tileSize);
        sf::Vector2f diff = tilePos - this->getPosition();
        float lenSquared = diff.x * diff.x + diff.y * diff.y;
        
        if (lenSquared <= 50) {
            m_path.pop_back();
            if (m_path.size() == 0)
                return;
            tilePos = m_room->getRealTilePos(m_path[m_path.size() - 1]) + sf::Vector2f(tileSize * getRand(0, 1.f), tileSize);
            diff = tilePos - this->getPosition();
            lenSquared = diff.x * diff.x + diff.y * diff.y;
        }
        float lenSqrt = sqrt(lenSquared);
        this->move(diff.x * dt * speed / lenSqrt, diff.y * dt * speed / lenSqrt);
    }
}

void Astronaut::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

int Astronaut::isAlive()
{
    return m_isAlive;
}

static int get_heuristic_cost(sf::Vector2i posA, sf::Vector2i posB)
{
    sf::Vector2i delta(abs(posA.x - posB.x), abs(posA.y - posB.y));

    if (delta.x > delta.y)
        return 14 * delta.y + 10 * (delta.x - delta.y);
  return 14 * delta.x + 10 * (delta.y - delta.x);
}

static bool vectContains(std::vector<node *> vect, Tile *tile)
{
    for (struct node *n : vect) {
        if (n->tile == tile)
            return true;
    }
    return false;
}

void Astronaut::resetPath(sf::Vector2f goal)
{
    node start;
    node end;

    start.tile = m_room->getTileAt(this->getPosition());
    start.cost = 0;
    start.heuristic_cost = 0;
    start.parent = nullptr;

    end.tile = m_room->getTileAt(goal);
    end.cost = 0;
    end.heuristic_cost = 0;
    end.parent = nullptr;
    computePath(&start, &end);
}

bool nodeCompare(node *na, node *nb) 
{
    if (na->cost == nb->cost)
        return na->heuristic_cost < nb->heuristic_cost;
    return na->cost < nb->cost;
}

void Astronaut::computePath(node *startNode, node *endNode)
{
    std::vector<node *> closed;
    std::vector<node *> opened;
    node *current;
    node *neighbour;
    int cost;
    int id = 0;
    m_path.clear();
    
    opened.push_back(startNode);
    while (!opened.empty()) {
        std::sort(opened.begin(), opened.end(), &nodeCompare);
        id = 0;
        if (opened.size() > 1 && opened[0]->cost == opened[1]->cost) {
            id = (getRand(0, 100) < 50) ? true : false;
        }
        current = opened[id];
        opened.erase(opened.begin() + id);
        closed.push_back(current);
        if (current->tile == endNode->tile) {
            while (current && current != startNode) {
                m_path.push_back(current->tile->getPosition());
                current = current->parent;
            }
            return;
        }
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                if (x == y && x == 0)
                    continue;
                neighbour = new node;
                neighbour->tile = m_room->getTile(current->tile->getPosition() + sf::Vector2i(x, y));
                if (!neighbour->tile || !neighbour->tile->isWalkable() || vectContains(closed, neighbour->tile)) {
                    delete neighbour;
                    continue;
                }
                if (x != 0 && y != 0) {
                    Tile *xTile = m_room->getTile(neighbour->tile->getPosition() + sf::Vector2i((x == 1) ? -1 : 1, 0));
                    Tile *yTile = m_room->getTile(neighbour->tile->getPosition() + sf::Vector2i(0, (y == 1) ? -1 : 1));;
                    if (!xTile || !xTile->isWalkable() || !yTile || !yTile->isWalkable()) {
                        delete neighbour;
                        continue;
                    }
                }
                cost = current->cost + get_heuristic_cost(current->tile->getPosition(), neighbour->tile->getPosition());
                if (cost < neighbour->cost || !vectContains(closed, neighbour->tile)) {
                    neighbour->cost = cost;
                    neighbour->heuristic_cost = get_heuristic_cost(neighbour->tile->getPosition(), endNode->tile->getPosition());
                    neighbour->parent = current;
                    if (!vectContains(opened, neighbour->tile)) {
                        opened.push_back(neighbour);
                        neighbour = 0;
                    }
                    else
                        delete neighbour;
                }
            }
        }
    }
}

bool Astronaut::seePos(sf::Vector2f pos)
{
    sf::Vector2f delta = pos - (this->getPosition());
    sf::Vector2i tilePos;
    sf::Vector2f pas(delta.x / 100.f, delta.y / 100.f);
    sf::Vector2f pos2 = this->getPosition();
    Tile *tile;

    for (int i = 0; i < 100; i++) {
        pos2 += pas;
        tile = m_room->getTileAt(pos2);
        if (!tile || !m_room->getTileAt(pos2)->isWalkable())
            return false;
    }
    return true;
}

void Astronaut::runAway(sf::Vector2f fleePos)
{
    sf::Vector2f diff = fleePos - (this->getPosition() - sf::Vector2f(0, m_sprite.getLocalBounds().height * 0.5));
    float diffLen = sqrt(diff.x * diff.x + diff.y * diff.y);
    float fleeDir = acos(diff.x / diffLen) * (180 / 3.14159265359f) + 90;
    float maxDist = 0;
    int bestDir = fleeDir;
    float currentDist;

    while (fleeDir >= 360 || fleeDir < 0) {
        fleeDir += (fleeDir < 0) ? 360 : -360;
    }
    for (int i = 0; i < 7; i++) {
        currentDist = getMaxDistInDir(fleeDir + i * 30);
        if (currentDist > maxDist) {
            maxDist = currentDist;
            bestDir = fleeDir + i * 30;
        }
    }
    if (bestDir == fleeDir - 90)
        m_move == sf::Vector2f(0, 0);
    else {
        bestDir *= (3.14159265359f / 180.f);
        m_move = sf::Vector2f(cos(bestDir) * 250, sin(bestDir) * 250);
    }
}

float Astronaut::getMaxDistInDir(float dir)
{
    float radDir = dir * (3.14159265359f / 180.f);
    sf::Vector2f vec(cos(radDir) * 10, sin(radDir) * 10);
    sf::Vector2f pos = this->getPosition() - sf::Vector2f(91, 90);
    int i = 0;

    Tile *tile = m_room->getTileAt(pos);
    while (m_room->getTileAt(pos)) {
        if (!m_room->getTileAt(pos)->isWalkable())
            break;
        i++;
        pos += vec;
        tile = m_room->getTileAt(pos);
    }
    return i * 10;
}
