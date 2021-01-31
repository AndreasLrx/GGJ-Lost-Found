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
        void draw(sf::RenderTarget& target, float interpolation);

        void pause() {};
        void resume() {};
        void end() {};

        GameDataRef getData() {return m_data;};

    private:
        enum GUI_ITEMS {PLAY_BUTTON, TUTORIAL_BUTTON, SETTINGS_BUTTON, QUIT_BUTTON};
        sf::RectangleShape m_background;
        sf::RectangleShape m_bg2;
        sf::RectangleShape m_title;
};

#endif /* !STATES_MENU_STATE_H */