/*
** EPITECH PROJECT, 2021
** GGJ Astronaut
** File description:
** base class
*/

#ifndef ASTRONAUT_HPP
#define ASTRONAUT_HPP

#include <vector>
#include "Entity/Astronauts/AbstractAstronaut.hpp"
#include "Map/Tile.hpp"
#include "Map/Room.hpp"

class Tile;

class Astronaut : public AbstractAstronaut
{
    public:
        Astronaut();
        ~Astronaut();

        void init();
        void initSprite(sf::Vector2f pos = sf::Vector2f(200, 200), sf::Vector2f scale = sf::Vector2f(50, 100));
        void handleInput(sf::Event event);
        void update(float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);

        int isAlive();
    
    private:
        struct node {
            Tile *tile;
            float cost;
            float heuristic_cost;
            struct node *parent;
        };
        
        bool nodeCompare(struct node *nodeA, struct node *nodeB);
        void computePath(struct node *startNode, struct node *endNode);
        bool vectContains(std::vector<struct node *> vect, Tile *tile);

        sf::Sprite m_sprite;
        sf::RectangleShape m_rect;


        //std::vector<sf::Vector2i> m_moves;
        std::vector<sf::Vector2i> m_path;
};

#endif /* !ASTRONAUT_HPP */