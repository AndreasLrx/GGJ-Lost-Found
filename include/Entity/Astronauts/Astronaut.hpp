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
        /*struct node {
            sf::Vector2i pos;
            float cost;
            float heuristic_cost;
        };
        bool nodeCompare(struct node nodeA, struct node nodeB);
        void computePath(struct node startNode, struct node endNode);*/

        sf::Sprite m_sprite;
        sf::RectangleShape m_rect;


        //std::vector<sf::Vector2i> m_moves;
        //std::vector<struct node> m_path;
};

#endif /* !ASTRONAUT_HPP */