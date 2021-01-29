/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** InputManager
*/

#include "GameEngine/InputManager.hpp"

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
{
    sf::Vector2i spriteSize(object.getLocalBounds().width, object.getLocalBounds().height);
    sf::IntRect spriteRect(static_cast<sf::Vector2i>(object.getPosition()), spriteSize);

    if (!sf::Mouse::isButtonPressed(button))
        return false;
    return spriteRect.contains(sf::Mouse::getPosition(window));
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
{
    return sf::Mouse::getPosition(window);
}