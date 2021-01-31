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

bool Entity::collidesWith(Entity const& other) const
{
    std::size_t countA;
    std::size_t countB;
    Circle const* boundsA = this->getCircleBounds(countA);
    Circle const* boundsB = other.getCircleBounds(countB);

    for (size_t i = 0; i < countA; ++i) {
        Circle c = boundsA[i];
        for (size_t j = 0; j < countB; ++j)
            if (c.collidesWith(boundsB[j]))
                return true;
    }
    return false;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::size_t count;
    Circle const* circles = this->getCircleBounds(count);

    //for (std::size_t i = 0; i < count; ++i)
        //circles[i].draw(target, states);
}
