/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** LevelSelectState
*/

#ifndef STATES_LEVEL_SELECT_H
#define STATES_LEVEL_SELECT_H

#include "GUI/GUIManager.hpp"
#include "GameEngine/Core.hpp"

class LevelSelectState : public State
{
    public:
        LevelSelectState(GameDataRef data);
        ~LevelSelectState();

        void init() {};

        void handleInput();
        void update(float dt);
        void draw(sf::RenderTarget& target, float interpolation);

        void pause() {};
        void resume() {};
        void end() {};

        GameDataRef getData() {return m_data;};

    private:
        void initBtn(std::string text, sf::Vector2f pos, int tag, inputReactFct input = nullptr);

        GameDataRef m_data;
};

#endif /* !STATES_LEVEL_SELECT_H */