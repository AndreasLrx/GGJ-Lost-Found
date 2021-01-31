/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** stateMachine
*/

#include <iostream>
#include "GameEngine/StateMachine.hpp"
#include "GameEngine/State.hpp"

StateMachine::StateMachine()
{
    m_isRemoving = false;
    m_isReplacing = false;
    m_isAdding = false;
}

void StateMachine::addState(StateRef newState, bool isReplacing)
{
    m_isAdding = true;
    m_isReplacing = isReplacing;
    m_newState = std::move(newState);
}

void StateMachine::removeState()
{
    m_isRemoving = true;
}

void StateMachine::processStateChanges()
{
    if (m_isRemoving && !m_states.empty()) {
        m_states.top()->end();
        m_states.pop();
        if (!m_states.empty())
            m_states.top()->resume();
        m_isRemoving = false;
    }
    if (m_isAdding) {
        if (!m_states.empty()) {
            if (m_isReplacing) {
                m_states.top()->end();
                m_states.pop();
            } else
                m_states.top()->pause();
        }
        m_states.push(std::move(m_newState));
        m_states.top()->init();
        m_isAdding = false;
    }
}

StateRef &StateMachine::GetActiveState()
{
    return m_states.top();
}