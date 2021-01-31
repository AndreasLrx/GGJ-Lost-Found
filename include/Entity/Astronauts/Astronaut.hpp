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
};

class Astronaut : public AbstractAstronaut
{
    public:
        Astronaut();
        ~Astronaut();

        virtual void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 });
        virtual void setAnimationListener() = 0;
        void setAlien(Alien *alien);
        void handleInput(sf::Event event);
        void onPositionChanged() override;
        void onOrientationChanged() override;
        void onScaleChanged() override;
        void update(float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int isAlive();

        void resetPath(sf::Vector2f goal);

        Circle const* getCircleBounds(std::size_t& size) const override;

        void takeDamage(float damage);

    protected:
        void changeState(int newState);
        void shoot();
        void cac();

        void computePath(node *startNode, node *endNode);
        bool seePos(sf::Vector2f pos);
        void updatePathTimer(float dt);
        void moveToPath(float speed, float dt);

        void runAway(sf::Vector2f fleePos);
        float getMaxDistInDir(float dir);

        AnimatedSprite m_sprite;
        int m_running;
        float m_pathUpdateTimer;

        sf::Vector2f m_move;
        std::vector<sf::Vector2i> m_path;

    private:
        Circle m_bounds[2];
};

#endif /* !ASTRONAUT_HPP */