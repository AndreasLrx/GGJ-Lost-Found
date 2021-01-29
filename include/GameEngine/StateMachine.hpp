/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** State Machine
*/

#ifndef GE_STATE_MACHINE_H
#define GE_STATE_MACHINE_H

#include <stack>
#include <memory>
#include "State.hpp"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
    public:
        StateMachine();
        ~StateMachine() {};

        void addState(StateRef newState, bool isReplacing = true);
        void removeState();

        void processStateChanges();

        StateRef &GetActiveState();

    private:
        std::stack<StateRef> m_states;
        StateRef m_newState;

        bool m_isRemoving;
        bool m_isReplacing;
        bool m_isAdding;
};

#endif /* !GE_STATE_MACHINE_H */