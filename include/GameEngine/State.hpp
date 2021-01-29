/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** State
*/

#ifndef GE_STATE_H
#define GE_STATE_H

class GUIManager;

class State
{
    public:
        State() {};
        virtual void init() = 0;

        virtual void handleInput() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(float interpolation) = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;
    
    protected:
        GUIManager *m_gui;
};

#endif /* !GE_STATE_H */