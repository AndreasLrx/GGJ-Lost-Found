/*
** EPITECH PROJECT, 2021
** GGJ Astronaut
** File description:
** base class
*/

#ifndef ASTRONAUT_HPP
#define ASTRONAUT_HPP

#include <vector>
#include "Entity/AnimatedSprite.hpp"
#include "Entity/Astronauts/AbstractAstronaut.hpp"
#include "Map/Tile.hpp"
#include "Map/Room.hpp"

class Tile;

struct node {
    Tile *tile;
    float cost;
    float heuristic_cost;
    node *parent;
    bool operator < (const node& n) const
    {
        return (cost > n.cost);
    }
};

class Astronaut : public AbstractAstronaut
{
    public:
        Astronaut();
        ~Astronaut();

        void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });
        void setAlien(Alien *alien);
        void setRoom(Room *room);
        void handleInput(sf::Event event);
        void onPositionChanged() override;
        void update(float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int isAlive();
        void resetPath(sf::Vector2f goal);
    
    protected:
        void computePath(node *startNode, node *endNode);
        bool seePos(sf::Vector2f pos);

        void runAway(sf::Vector2f fleePos);
        float getMaxDistInDir(float dir);

        AnimatedSprite m_sprite;
        int m_running;
        float m_pathUpdateTimer;

        sf::Vector2f m_move;
        std::vector<sf::Vector2i> m_path;
};

#endif /* !ASTRONAUT_HPP */