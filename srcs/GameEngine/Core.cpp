/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** Core
*/

#include "GameEngine/Core.hpp"
#include "States/MenuState.hpp"
#include <iostream>

Core::Core(unsigned int width, unsigned int height, \
std::string title, sf::Uint32 style)
{
    m_data->wind.create(sf::VideoMode(width, height, 32), title, style);
    m_data->assets.loadAll();
    m_data->machine.addState(StateRef(new MenuState(m_data)));
    run();
}

void Core::run()
{
    float newTime;
    float frameTime;
    float interpolation;
    float currentTime = m_clock.getElapsedTime().asSeconds();
    float acccumulator = 0;

    while (m_data->wind.isOpen()) {
        m_data->machine.processStateChanges();
        newTime = m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        currentTime = newTime;
        if (frameTime > 0.25f)
            frameTime = 0.25f;
        acccumulator += frameTime;
        while (acccumulator >= dt) {
            m_data->machine.GetActiveState()->handleInput();
            m_data->machine.GetActiveState()->update(dt);
            acccumulator -= dt;
        }
        interpolation = acccumulator / dt;
        m_data->machine.GetActiveState()->draw(interpolation);
    }
}
