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

class Astronaut : public AbstractAstronaut
{
    public:
        Astronaut();
        ~Astronaut();

        void init(Alien *alien, sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });
        void handleInput(sf::Event event);
        void update(float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);

        int isAlive();
        void resetPath();
    
    private:
        struct node {
            Tile *tile;
            float cost;
            float heuristic_cost;
            struct node *parent;
            bool operator < (const struct node& n) const
            {
                return (cost > n.cost);
            }
        };
        void computePath(struct node *startNode, struct node *endNode);
        bool vectContains(std::vector<struct node *> vect, Tile *tile);
        bool seePos(sf::Vector2f pos);

        void runAway(sf::Vector2f fleePos);
        float getMaxDistInDir(float dir);

        AnimatedSprite m_sprite;
        float m_pathUpdateTimer;


        //std::vector<sf::Vector2i> m_moves;
        std::vector<sf::Vector2i> m_path;
};

#endif /* !ASTRONAUT_HPP */