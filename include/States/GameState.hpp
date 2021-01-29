/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameState
*/

#ifndef STATE_GAME_STATE_H
#define STATE_GAME_STATE_H

#include "GameEngine/Core.hpp"
#include "GUI/GUIManager.hpp"

class GameState : public State
{
    public:
        GameState(GameDataRef data);
        ~GameState();

        void init() {};

        void handleInput();
        void update(float dt);
        void draw(float interpolation);

        void pause() {};
        void resume() {};

    private:
        GameDataRef m_data;
};

#endif /* !STATE_GAME_STATE_H */