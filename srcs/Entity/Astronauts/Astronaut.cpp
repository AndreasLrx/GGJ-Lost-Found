/*
** EPITECH PROJECT, 2021
** GGJ Astronauts
** File description:
** Astronaut
*/

#include "Entity/Astronauts/Astronaut.hpp"

Astronaut::Astronaut()
{

}

Astronaut::~Astronaut()
{

}

void Astronaut::init()
{

}

void Astronaut::initSprite(sf::Vector2f pos, sf::Vector2f scale)
{
    m_rect.setPosition(pos);
    m_rect.setSize(scale);
    m_rect.setFillColor(sf::Color::Blue);
}

void Astronaut::handleInput(sf::Event event)
{

}

void Astronaut::update(float dt)
{

}

void Astronaut::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect, states);
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

static int get_heuristic_cost(sf::Vector2f posA, sf::Vector2f posB)
{
    sf::Vector2f delta = posA - posB;

    if (delta.x > delta.y)
        return 14 * delta.y + 10 * (delta.x - delta.y);
  return 14 * delta.x + 10 * (delta.y - delta.x);
}

static int get_heuristic_cost(sf::Vector2i posA, sf::Vector2i posB)
{
    sf::Vector2i delta = posA - posB;

    if (delta.x > delta.y)
        return 14 * delta.y + 10 * (delta.x - delta.y);
  return 14 * delta.x + 10 * (delta.y - delta.x);
}

bool Astronaut::nodeCompare(struct node *nodeA, struct node *nodeB)
{
    return (nodeA->cost > nodeB->cost);
}

bool Astronaut::vectContains(std::vector<struct node *> vect, Tile *tile)
{
    for (struct node *n : vect) {
        if (n->tile == tile)
            return true;
    }
    return false;
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
        std::sort(opened.begin(), opened.end(), nodeCompare);
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
                if (!neighbour->tile->isWalkable() || vectContains(closed, neighbour->tile))
                    continue;
                cost = current->cost + get_heuristic_cost(current->tile->getPosition(), neighbour->tile->getPosition());
                if (cost < neighbour->cost || !vectContains(closed, neighbour->tile)) {
                    neighbour->cost = cost;
                    neighbour->heuristic_cost = get_heuristic_cost(neighbour->tile->getPosition(), endNode->tile->getPosition());
                    neighbour->parent = current;
                if (!vectContains(opened, neighbour->tile))
                    opened.push_back(neighbour);
                }
            }
        }
    }
}