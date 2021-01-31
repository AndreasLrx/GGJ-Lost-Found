/*
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Entity
*/

#include "Entity/Entity.hpp"
#include "States/GameState.hpp"

void Entity::spawnProjectile(AbstractProjectile* projectile)
{
	this->m_room->spawnProjectile(projectile, this);
}

GameDataRef Entity::getGameData()
{
    return this->m_room->getGameData();
}

void Entity::setRoom(Room *room)
{
    this->m_room = room;
}

Circle const* Entity::getCircleBounds(std::size_t& size) const
{

    size = 0;
    return nullptr;
}

#include <iostream>
bool Entity::collidesWith(Entity const& other) const
{
    std::size_t countA;
    std::size_t countB;
    Circle const* boundsA = this->getCircleBounds(countA);
    Circle const* boundsB = other.getCircleBounds(countB);

    for (size_t i = 0; i < countA; ++i) {
        Circle c = boundsA[i];
        for (size_t j = 0; i < countB; ++j)
            if (c.collidesWith(boundsB[j])) {
                std::cout << "COLLISION: ax: " << c.m_pos.x << ", ay: " << c.m_pos.y << ", ar: " << c.m_radius << " | bx: " << boundsB[j].m_pos.x << ", by: " << boundsB[j].m_pos.y << ", br:" << boundsB[j].m_radius << std::endl;
                return true;
            }
    }
    return false;
}

#include <iostream>
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::size_t count;
    Circle const* circles = this->getCircleBounds(count);

    for (std::size_t i = 0; i < count; ++i) {
        //std::cout << "x: " << circles[i].m_pos.x << ", y: " << circles[i].m_pos.y << ", radius: " << circles[i].m_radius << std::endl;
        circles[i].draw(target, states);
    }
}
