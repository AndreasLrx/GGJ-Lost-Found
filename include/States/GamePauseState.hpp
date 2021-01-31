/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GamePauseState
*/

#ifndef STATES_GAME_PAUSE_H
#define STATES_GAME_PAUSE_H

#include "GUI/GUIManager.hpp"
#include "GameEngine/Core.hpp"

class GamePauseState : public State
{
    public:
        GamePauseState(GameDataRef data);
        ~GamePauseState();

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
        sf::RectangleShape m_background;
        sf::RectangleShape m_menu;
        sf::RenderTexture m_texture;
};

#endif /* !STATES_GAME_PAUSE_H */