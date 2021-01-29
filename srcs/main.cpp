/*
** EPITECH PROJECT, 2021
** GGJ
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include "GameEngine/Core.hpp"

int main(int argc, char **argv)
{
    Core core(1280, 720, "SFML Base", sf::Style::Close | sf::Style::Titlebar);
    return 0;
}