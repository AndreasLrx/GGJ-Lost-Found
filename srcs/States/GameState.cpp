/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameState
*/

#include "States/GameState.hpp"
#include "Map/Floor.hpp"
#include <iostream>

GameState::GameState(GameDataRef data)
{
    m_floor = nullptr;
    m_data = data;
    m_gui = new GUIManager(data);
    m_astronaut.init(*m_data->assets.getTexture("squares"), sf::Vector2f(100, 100), sf::Vector2f(2.5, 2.5));
}

GameState::~GameState()
{
    delete m_gui;
}

void GameState::init()
{
    this->m_floor = new Floor(this->m_data);
    //this->m_floor = this->m_floor.set("11111111");
}

void GameState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        m_gui->handleInput(event);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            m_data->machine.removeState();
    }
}

void GameState::update(float dt)
{
    m_floor->change_room("1");
    m_gui->update(dt);
    m_astronaut.update(dt);
}

void GameState::draw(float interpolation)
{
    m_data->wind.clear(sf::Color::Black);
    m_data->wind.draw(*this->m_floor->get_room());
    m_data->wind.draw(m_astronaut);
    m_gui->draw(interpolation);
    m_data->wind.display();
}
