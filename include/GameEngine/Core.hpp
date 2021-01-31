/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** Core class
*/

#ifndef GE_CORE_H
#define GE_CORE_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameEngine/StateMachine.hpp"
#include "GameEngine/AssetManager.hpp"
#include "GameEngine/InputManager.hpp"
#include "GameEngine/Settings.hpp"
#include "GameEngine/macro.hpp"

struct GameData {
    StateMachine machine;
    sf::RenderWindow wind;
    AssetManager assets;
    InputManager input;
    Settings settings;
    int datas;
};

class Core
{
    public:
        Core(unsigned int width, unsigned int height, std::string title, sf::Uint32 style);
        ~Core() {};
    
    private:
        void run();

        const float dt = 1.0f / 60.0f;
        sf::Clock m_clock;
        GameDataRef m_data = std::make_shared<GameData>();
};

#endif /* !GE_CORE_H */