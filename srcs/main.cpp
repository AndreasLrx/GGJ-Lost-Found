/*
** EPITECH PROJECT, 2021
** GGJ
** File description:
** main
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameEngine/Core.hpp"

int main(int argc, char **argv)
{
    if (argc == 2 &&  std::string(argv[1]) == std::string("-h")) {
        std::cout<<"set desc"<<std::endl;
        return 0;
    }
    srand(time(NULL));
    Core core(1280, 720, "An Eye to Rul'em All", sf::Style::Close | sf::Style::Titlebar);
    return 0;
}