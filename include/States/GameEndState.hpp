/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameEnd
*/

#ifndef STATES_GAME_END_H
#define STATES_GAME_END_H

#include "GUI/GUIManager.hpp"
#include "GameEngine/Core.hpp"

class GameEndState : public State
{
    public:
        GameEndState(GameDataRef data);
        ~GameEndState();

        void init() {};

        void handleInput();
        void update(float dt);
        void draw(sf::RenderTarget& target, float interpolation);

        void pause() {};
        void resume() {};
        void end() {};

        GameDataRef getData() {return m_data;};

    private:

        GameDataRef m_data;
        sf::RectangleShape m_backgroundInit;
        sf::RectangleShape m_endBackground;
        sf::RenderTexture m_texture;
        float m_timer;
        int m_endReady;
};

#endif /* !STATES_GAME_END_H */