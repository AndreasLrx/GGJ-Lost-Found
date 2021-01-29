/*
** EPITECH PROJECT, 2021
** Test
** File description:
** Test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include "Entity/Entity.hpp"

class Test : public Entity
{
    public:
        Test() {};
        ~Test() {};

        void init(sf::Vector2f pos, sf::Texture *texture);
        void handleInput(sf::Event event) {};
        void update(float dt) {};
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2f getPosition() {return m_sprite.getPosition();};
        void setPosition(sf::Vector2f pos) {};
        void setPosition(float x, float y) {};

        int isAlive() {return true;};

    private:
        sf::Sprite m_sprite;
};

#endif /* !TEST_HPP_ */
