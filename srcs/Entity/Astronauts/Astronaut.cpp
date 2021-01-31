/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Astronaut
*/

#include <cmath>
#include <iostream>
#include "Entity/Astronauts/Astronaut.hpp"
#include "Entity/Alien.hpp"
#include "functions.hpp"
#include "Entity/Projectiles/LaserProjectile.hpp"

Astronaut::Astronaut()
{
    m_pathUpdateTimer = 5;
    this->setOrientation(0);
    this->m_running = false;
    this->m_bounds[0] = Circle();
    this->m_bounds[1] = Circle();
}

Astronaut::~Astronaut()
{

}

void Astronaut::init(sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::FloatRect bounds;
    sf::IntRect *move = new sf::IntRect[4]{{0, 0, 400, 400}, {400, 0, 400, 400}, {800, 0, 400, 400}, {1200, 0, 400, 400}};
    sf::IntRect *idle = new sf::IntRect[1]{{0, 400, 400, 400}};
    sf::IntRect *cac = new sf::IntRect[1]{{400, 400, 400, 400}};
    sf::IntRect *shoot = new sf::IntRect[1]{{800, 400, 400, 400}};
	sf::IntRect *move_shoot = new sf::IntRect[4]{{0, 800, 400, 400}, {400, 800, 400, 400}, {800, 800, 400, 400}, {1200, 800, 400, 400}};
    m_animTextRectTabs[MOVE] = move;
    m_animTextRectTabs[IDLE] = idle;
    m_animTextRectTabs[CAC] = cac;
    m_animTextRectTabs[SHOOT] = shoot;
    m_animTextRectTabs[MOVE_SHOOT] = move_shoot;
    m_animDatas[MOVE] = {6.f, 4};
    m_animDatas[IDLE] = {6.f, 1};
    m_animDatas[CAC] = {6.f, 1};
    m_animDatas[SHOOT] = {2.f, 1};
    m_animDatas[MOVE_SHOOT] = {6.f, 4};

    m_move = sf::Vector2f(0, 0);
    m_running = 0;
    m_state = MOVE;
    m_attackCooldown = 0;
    this->m_sprite.setTexture(texture);
    this->m_sprite.setPosition(pos);
    this->m_sprite.setScale(scale);
    this->changeState(MOVE);
    this->setPosition(pos);
    this->setScale(scale);
    m_sprite.update(0);
    bounds = m_sprite.getLocalBounds();
    this->m_sprite.setOrigin(bounds.width / 2.f, bounds.height);
    this->m_sprite.setMirrored(true);
    setAnimationListener();
}

void Astronaut::setAlien(Alien *alien)
{
    m_alien = alien;
}

void Astronaut::cac()
{
    if (m_attackCooldown > 1.f) {
        //attack
        changeState(CAC);
        m_attackCooldown = 0;
    }
}

void Astronaut::shoot()
{
    if (m_attackCooldown > 2.f && m_state != SHOOT && m_state != MOVE_SHOOT) {
	    LaserProjectile* laser = new LaserProjectile();
        sf::FloatRect bounds = this->m_sprite.getGlobalBounds();
        sf::Vector2f laserPos = sf::Vector2f(bounds.left + bounds.width / 10, bounds.top + bounds.height / 2);
	    sf::Vector2f laserVec = laserPos - this->m_alien->getPosition();
	    float angle = atan2(laserVec.y, laserVec.x);

        laser->init(*this->getGameData()->assets.getTexture("laser"), laserPos, sf::Vector2f(2.5, 2.5));
	    laser->setOrientation(toDegrees(angle) + 180.0);
	    this->spawnProjectile(laser);
        changeState((m_state == AbstractAstronaut::MOVE) ? AbstractAstronaut::MOVE_SHOOT : AbstractAstronaut::SHOOT);
        m_attackCooldown = 0;
    }
}

void Astronaut::changeState(int newState)
{
    this->m_sprite.setTextureFrames(m_animDatas[newState].second, m_animTextRectTabs[newState]);
    this->m_sprite.setAnimationSpeed(m_animDatas[newState].first);
    m_state = newState;
    this->m_sprite.resetFrame();
}

void Astronaut::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
        return;
}

Circle const* Astronaut::getCircleBounds(std::size_t& size) const
{
    size = 2;
    return this->m_bounds;
}

void Astronaut::onPositionChanged()
{
    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

	this->m_sprite.setPosition(this->getPosition());
    this->m_bounds[0].m_pos = sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.width / 3.0f);
    this->m_bounds[1].m_pos = sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + (2.0f * bounds.width / 3.0f));
}

void Astronaut::onOrientationChanged()
{
    float angle = this->getOrientation();

    if (angle >= 270.0f || angle < 90.0f)
        this->m_sprite.setMirrored(true);
    else
        this->m_sprite.setMirrored(false);
}

void Astronaut::onScaleChanged()
{
    sf::FloatRect bounds = this->m_sprite.getGlobalBounds();

    this->m_bounds[0].m_radius = bounds.width / 3;
    this->m_bounds[1].m_radius = bounds.width / 3;
}

void Astronaut::update(float dt)
{
	sf::Vector2f lookVec = this->getPosition() - this->m_alien->getPosition();
	float angle = atan2(lookVec.y, lookVec.x);

    (void)dt;
    this->setOrientation(toDegrees(angle) + 180.0);
}

void Astronaut::updatePathTimer(float dt)
{
    m_attackCooldown += dt;
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
    Entity::draw(target, states);
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
    if (start.tile == nullptr || end.tile == nullptr)
        return;
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

    while (m_room->getTileAt(pos)) {
        if (!m_room->getTileAt(pos)->isWalkable())
            break;
        i++;
        pos += vec;
    }
    return i * 10;
}

void Astronaut::takeDamage(float damage)
{
    if (damage <= 0.0f)
        return;
    this->m_isAlive = false;
}
