/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** Menu State
*/

#ifndef STATES_MENU_STATE_H
#define STATES_MENU_STATE_H

#include <SFML/Graphics.hpp>
#include "GameEngine/State.hpp"
#include "GameEngine/Core.hpp"
#include "GUI/GUIManager.hpp"

class MenuState : public State
{
    public:
        MenuState(GameDataRef data);
        ~MenuState();

        void init() {};

        void handleInput();
        void update(float dt);
        void draw(float interpolation);

        void pause() {};
        void resume() {};

    private:
        GameDataRef m_data;
};

#endif /* !STATES_MENU_STATE_H */