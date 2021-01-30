/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Astronaut
*/

#include "Entity/Astronauts/Astronaut.hpp"

Astronaut::Astronaut()
{
    m_pathUpdateTimer = 5;
}

Astronaut::~Astronaut()
{

}

void Astronaut::init()
{

}

void Astronaut::initSprite(sf::Texture *texture, sf::Vector2f pos, sf::Vector2f scale)
{
    sf::IntRect frames[] = { {0, 0, 32, 32}, {32, 0, 32, 32}, {64, 0, 32, 32}, {96, 0, 32, 32}, {0, 32, 32, 32}, {32, 32, 32, 32}, {64, 32, 32, 32}, {96, 32, 32, 32} };

    m_sprite.setTexture(*texture);
    this->m_sprite.setTextureFrames(8, frames);
    this->m_sprite.setAnimationSpeed(3.25f);
    m_sprite.setPosition(pos);
    m_sprite.setScale(scale);
}

void Astronaut::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
        return;
}

void Astronaut::update(float dt)
{
    /*
    //if dist < max_po && seepos
    //  empty path, shoot, walk back return
    m_pathUpdateTimer += dt;
    if (m_pathUpdateTimer >= 1) {
        m_pathUpdateTimer = 0;
        resetPath();
    }
    sf::Vector2i nextPos = m_path[m_path.size() - 1];
    sf::Vector2f posTile(nextPos.x * 32, nextPos.y * 32);
    sf::Vector2f diff = posTile - m_sprite.getPosition();

    if (diff.x * diff.x + diff.y * diff.y <= 5) {
        m_path.pop_back();
        nextPos = m_path[m_path.size() - 1];
        posTile = sf::Vector2f(nextPos.x * 32, nextPos.y * 32);
        diff = posTile - m_sprite.getPosition();
    }
    m_sprite.move(diff * (dt * 50));
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_sprite.move(0, -200 * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_sprite.move(-200 * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_sprite.move(0, 200 * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_sprite.move(200 * dt, 0);
    this->m_sprite.update(dt);
}

void Astronaut::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

sf::Vector2f Astronaut::getPosition()
{
    return m_sprite.getPosition();
}

void Astronaut::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

void Astronaut::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

int Astronaut::isAlive()
{
    return m_isAlive;
}

static int get_heuristic_cost(sf::Vector2i posA, sf::Vector2i posB)
{
    sf::Vector2i delta = posA - posB;

    if (delta.x > delta.y)
        return 14 * delta.y + 10 * (delta.x - delta.y);
  return 14 * delta.x + 10 * (delta.y - delta.x);
}

bool Astronaut::vectContains(std::vector<struct node *> vect, Tile *tile)
{
    for (struct node *n : vect) {
        if (n->tile == tile)
            return true;
    }
    return false;
}

void Astronaut::resetPath()
{
    struct node start;
    struct node end;

    start.tile = m_room->getTile(sf::Vector2i(m_sprite.getPosition().x / 32, m_sprite.getPosition().y / 32));
    start.cost = 0;
    start.heuristic_cost = 0;
    start.parent = nullptr;

    end.tile = m_room->getTile(sf::Vector2i(15, 20));
    end.cost = 0;
    end.heuristic_cost = 0;
    end.parent = nullptr;
    computePath(&start, &end);
}

void Astronaut::computePath(struct node *startNode, struct node *endNode)
{
    std::vector<struct node *> closed;
    std::vector<struct node *> opened;
    struct node *current;
    struct node *neighbour;
    int cost;
    m_path.empty();

    opened.push_back(startNode);
    while (!opened.empty()) {
        std::sort(opened.begin(), opened.end());
        current = opened.at(opened.size() - 1);
        opened.pop_back();
        if (current->tile == endNode->tile) {
            while (current != startNode) {
                m_path.push_back(current->tile->getPosition());
                current = current->parent;
            }
            return;
        }
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                if (x == y && x == 0)
                    continue;
                neighbour = new struct node;
                neighbour->tile = m_room->getTile(current->tile->getPosition() + sf::Vector2i(x, y));
                if (!neighbour->tile->isWalkable() || vectContains(closed, neighbour->tile)) {
                    delete neighbour;
                    continue;
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
    sf::Vector2f delta = pos - m_sprite.getPosition();
    sf::Vector2i tilePos;
    sf::Vector2f pas(delta.x / 100.f, delta.y / 100.f);
    sf::Vector2f pos2 = m_sprite.getPosition();

    for (int i = 0; i < 100; i++) {
        pos2 += pas;
        if (!m_room->getTile(sf::Vector2i(pos2.x / 32, pos2.y / 32))->isWalkable())
            return false;
    }
    return true;
}