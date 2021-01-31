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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    m_data->wind.create(sf::VideoMode(width, height, 32), title, style, settings);
    m_data->assets.loadAll();
    m_data->settings.setWindSize(width, height);
    m_data->machine.addState(StateRef(new MenuState(m_data)));
    m_data->datas = 0;
    sf::Image icon;
    icon.loadFromFile("res/Textures/icon.png");
    m_data->wind.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    run();
    m_data->assets.stopMusics();
    m_data->assets.stopSounds();
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
        m_data->machine.GetActiveState()->draw(m_data->wind, interpolation);
        m_data->wind.display();
        m_data->assets.updateSounds();
    }
}
