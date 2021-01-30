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
#include "Entity/Astronauts/Astronaut.hpp"
#include "Map/Tile.hpp"
#include "Map/Floor.hpp"

class GameState : public State
{
    public:
        GameState(GameDataRef data);
        ~GameState();

        void init();

        void handleInput();
        void update(float dt);
        void draw(float interpolation);

        void pause() {};
        void resume() {};

    private:
        GameDataRef m_data;
        Astronaut m_astronaut;
        Floor m_Floor;
};

#endif /* !STATE_GAME_STATE_H */
