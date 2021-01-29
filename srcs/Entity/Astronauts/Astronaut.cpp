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

/*static int get_heuristic_cost(sf::Vector2f posA, sf::Vector2f posB)
{
    sf::Vector2f delta = posA - posB;

    if (delta.x > delta.y)
        return 14 * delta.y + 10 * (delta.x - delta.y);
  return 14 * delta.x + 10 * (delta.y - delta.x);
}

bool Astronaut::nodeCompare(struct node nodeA, struct node nodeB)
{
    return (nodeA.cost > nodeB.cost);
}

void Astronaut::computePath(struct node startNode, struct node endNode)
{
    std::vector<struct node> closed;
    std::vector<struct node> opened;
    struct node current;
    int cost;

    opened.push_back(startNode);
    while (!opened.empty()) {
        std::sort(opened.begin(), opened.end(), nodeCompare);
        current = opened.at(opened.size() - 1);
        opened.pop_back();
        if (current.pos == endNode.pos) {
            //found;
            return;
        }
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (x == y && x == 1)
                    continue;
                if (!tile.isWalkable() || std::find(closed, tile))
                    continue;
                cost = current.cost + get_heuristic_cost(current, tile);
                if (cost < tile.cost || !std::find(closed, tile)) {
                    tile.cost = cost;
                    tile.heuristic_cost = get_heuristic_cost(tile, endNode);
                    tile.parent = current;

                if (!std::find(opened, tile))
                    opened.push_back(tile);
                }
            }
        }
    }
    //no path;
}*/