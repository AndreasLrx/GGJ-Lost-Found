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
#include "Entity/Astronauts/Shooter.hpp"
#include "Entity/Astronauts/Scientist.hpp"
#include "Entity/Alien.hpp"
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

        GameDataRef getData() {return m_data;};

    private:
        Scientist m_scientist;
        Shooter m_shooter;
        Alien m_alien;
        Floor *m_floor;
};

#endif /* !STATE_GAME_STATE_H */
