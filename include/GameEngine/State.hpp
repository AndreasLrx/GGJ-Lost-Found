/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** State
*/

#ifndef GE_STATE_H
#define GE_STATE_H

#include <SFML/Graphics.hpp>
#include "GameEngine/macro.hpp"

class GUIManager;

class State
{
    public:
        State() {};
        virtual void init() = 0;

        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderTarget& target, float interpolation) = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual void end() = 0;

        virtual GameDataRef getData() = 0;
    
    protected:
        GUIManager *m_gui;
        GameDataRef m_data;
};

#endif /* !GE_STATE_H */