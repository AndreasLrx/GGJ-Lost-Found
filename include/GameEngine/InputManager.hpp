/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** InputManager
*/

#ifndef GE_INPUT_MANAGER_H
#define GE_INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

class InputManager {
    public:
        InputManager() {};
        ~InputManager() {};

        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        sf::Vector2i getMousePosition(sf::RenderWindow &window);

    private:
};

#endif /* !GE_INPUT_MANAGER_H */