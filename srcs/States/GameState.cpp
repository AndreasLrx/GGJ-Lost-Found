/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameState
*/

#include "States/GameState.hpp"
#include "States/GamePauseState.hpp"
#include "Map/Floor.hpp"
#include "States/GameEndState.hpp"
#include <iostream>

GameState::GameState(GameDataRef data): m_alien(data)
{
    m_floor = nullptr;
    m_data = data;
    m_gui = new GUIManager(data);
    m_alien.init(*m_data->assets.getTexture("alien"), sf::Vector2f(200, 200), sf::Vector2f(0.25, 0.25));
    m_data->assets.playMusic("battletheme");
    m_data->assets.getMusic("ambiant")->setVolume(60);
    m_data->assets.playMusic("ambiant");
}

GameState::~GameState()
{
    delete m_gui;
}

void GameState::init()
{
    this->m_floor = new Floor(this->m_data, &m_alien, m_data->datas);
}

void GameState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        m_gui->handleInput(event);
        this->m_alien.handleInput(event);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            m_data->machine.addState(StateRef(new GamePauseState(m_data)), 0);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U) {
            m_data->datas = 1;
            m_data->machine.addState(StateRef(new GameEndState(m_data)), 0);
        }

        m_floor->handleInput(event);
    }
}

void GameState::update(float dt)
{
    m_floor->change_room(dt, "1");
    m_gui->update(dt);
    if (m_alien.isAlive())
        m_alien.update(dt);
    if (!m_alien.isAlive()) {
        m_data->datas = 2;
        m_data->machine.addState(StateRef(new GameEndState(m_data)), 0);
    }
}

void GameState::draw(sf::RenderTarget& target, float interpolation)
{
    target.clear(sf::Color::Black);
    target.draw(*this->m_floor->get_room());
    if (m_alien.isAlive())
        target.draw(this->m_alien);
    m_gui->draw(interpolation);
}
