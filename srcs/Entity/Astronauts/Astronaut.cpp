/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Astronaut
*/

#include <iostream>
#include "Entity/Astronauts/Astronaut.hpp"
#include "Entity/Alien.hpp"

static float getRand(float min, float max)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

Astronaut::Astronaut()
{
    m_pathUpdateTimer = 5;
    this->setOrientation(getRand(0, 360));
}

Astronaut::~Astronaut()
{

}

void Astronaut::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::FloatRect bounds;
	sf::IntRect frames[] = { {0, 0, 250, 250}, {250, 0, 250, 250}, {500, 0, 250, 250}, {750, 0, 250, 250}};

    m_move = sf::Vector2f(0, 0);
    this->m_sprite.setTexture(texture);
    this->m_sprite.setPosition(pos);
    this->m_sprite.setScale(scale);
    this->m_sprite.setTextureFrames(4, frames);
    this->m_sprite.setAnimationSpeed(3.25f);
    this->setPosition(pos);
    this->setScale(scale);
    m_sprite.update(0);
    bounds = m_sprite.getLocalBounds();
    this->m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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

static double distSquared(sf::Vector2f p1, sf::Vector2f p2)
{
    return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

void Astronaut::onPositionChanged()
{
	this->m_sprite.setPosition(this->getPosition());
}

void Astronaut::update(float dt)
{
    this->m_sprite.update(dt);
    float dist = distSquared(m_sprite.getPosition(), m_alien->getPosition());
    if (dist < 160000 && seePos(m_alien->getPosition())) {
        m_path.clear();
        //shoot
        //flee if needed
        return;
    }
    m_pathUpdateTimer += dt;
    if (m_pathUpdateTimer >= 1) {
        m_pathUpdateTimer = 0;
        resetPath();
        //runAway(m_alien->getPosition());
    }
    if (m_path.size() != 0) {
        sf::Vector2i nextPos = m_path[m_path.size() - 1];
        sf::Vector2f posTile(nextPos.x * 128, nextPos.y * 128);
        sf::Vector2f diff = posTile - this->getPosition();
        float lenSquared = diff.x * diff.x + diff.y * diff.y;

        if (lenSquared <= 400) {
            m_path.pop_back();
            if (m_path.size() == 0)
                return;
            nextPos = m_path[m_path.size() - 1];
            posTile = sf::Vector2f(nextPos.x * 128, nextPos.y * 128);
            diff = posTile - this->getPosition();
            lenSquared = diff.x * diff.x + diff.y * diff.y;
        }
        float lenSqrt = sqrt(lenSquared);
        this->move(diff.x * (dt * 200) / lenSqrt, diff.y * dt * 200 / lenSqrt);
    }
    
    //this->move(m_move * dt);
    
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

bool Astronaut::vectContains(std::vector<node *> vect, Tile *tile)
{
    for (struct node *n : vect) {
        if (n->tile == tile)
            return true;
    }
    return false;
}

void Astronaut::resetPath()
{
    node start;
    node end;

    start.tile = m_room->getTileAt(this->getPosition());
    start.cost = 0;
    start.heuristic_cost = 0;
    start.parent = nullptr;

    end.tile = m_room->getTileAt(m_alien->getPosition());
    end.cost = 0;
    end.heuristic_cost = 0;
    end.parent = nullptr;
    computePath(&start, &end);
}

bool nodeCompare(node *na, node *nb) 
{
    return (na->cost >= nb->cost);
}

void Astronaut::computePath(node *startNode, node *endNode)
{
    std::vector<node *> closed;
    std::vector<node *> opened;
    node *current;
    node *neighbour;
    int cost;
    m_path.clear();

    opened.push_back(startNode);
    while (!opened.empty()) {
        std::sort(opened.begin(), opened.end(), &nodeCompare);
        current = opened.at(opened.size() - 1);
        closed.push_back(current);
        opened.pop_back();
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
                    if (!vectContains(opened, neighbour->tile))
                        opened.push_back(neighbour);
                    else
                        delete neighbour;
                }
            }
        }
    }
}

bool Astronaut::seePos(sf::Vector2f pos)
{
    sf::Vector2f delta = pos - this->getPosition();
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
    sf::Vector2f diff = fleePos - this->getPosition();
    float diffLen = sqrt(diff.x * diff.x + diff.y * diff.y);
    float fleeDir = acos(diff.x / diffLen) * (180 / 3.14159265359f) + 90;
    float maxDist = 0;
    int bestDir = fleeDir + 90;
    float currentDist;

    while (fleeDir >= 360 || fleeDir < 0)
        fleeDir += (fleeDir < 0) ? 360 : -360;
    for (int i = 0; i < 7; i++) {
        currentDist = getMaxDistInDir(fleeDir + i * 30);
        if (currentDist > maxDist) {
            maxDist = currentDist;
            bestDir = fleeDir + i * 30;
        }
    }
    bestDir *= (3.14159265359f / 180.f);
    
    m_move = sf::Vector2f(cos(bestDir) * 200, sin(bestDir) * 200);
}

float Astronaut::getMaxDistInDir(float dir)
{
    float radDir = dir * (3.14159265359f / 180.f);
    sf::Vector2f vec(cos(radDir) * 10, sin(radDir) * 10);
    sf::Vector2f pos = this->getPosition();
    int i = 0;

    while (m_room->getTileAt(pos) && m_room->getTileAt(pos)->isWalkable()) {
        i++;
        pos += vec;
    }
    return i * 10;
}
