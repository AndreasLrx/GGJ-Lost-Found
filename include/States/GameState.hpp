/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameState
*/

#ifndef STATE_GAME_STATE_H
#define STATE_GAME_STATE_H

#include <map>
#include "GameEngine/Core.hpp"
#include "GUI/GUIManager.hpp"
#include "Entity/Astronauts/Soldier.hpp"
#include "Entity/Astronauts/Scientist.hpp"
#include "Entity/Astronauts/Berserk.hpp"
#include "Entity/Projectiles/LaserProjectile.hpp"
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
        Alien *getAlien() {return &m_alien;};

        void spawnProjectile(AbstractProjectile* projectile, Entity* owner = nullptr);

    private:
        Scientist m_scientist;
        Soldier m_shooter;
        Alien m_alien;
        Floor *m_floor;
        AbstractProjectile* m_projectile;
};

#endif /* !STATE_GAME_STATE_H */
