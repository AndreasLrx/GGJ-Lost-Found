/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameState
*/

#include "States/GameState.hpp"
#include "Map/Floor.hpp"
#include <iostream>

GameState::GameState(GameDataRef data): m_alien(data)
{
    m_floor = nullptr;
    m_data = data;
    m_gui = new GUIManager(data);
    m_alien.init(*m_data->assets.getTexture("alien"), sf::Vector2f(200, 200), sf::Vector2f(0.25, 0.25));
    m_scientist.init(*m_data->assets.getTexture("astronaut"), sf::Vector2f(1100, 100), sf::Vector2f(0.5, 0.5));
    m_scientist.setAlien(&m_alien);
    m_shooter.init(*m_data->assets.getTexture("astronaut"), sf::Vector2f(500, 600), sf::Vector2f(0.5, 0.5));
    m_shooter.setAlien(&m_alien);
}

GameState::~GameState()
{
    delete m_gui;
}

void GameState::init()
{
    this->m_floor = new Floor(this->m_data);
    m_scientist.setRoom(m_floor->get_room());
    m_shooter.setRoom(m_floor->get_room());
    //this->m_floor = this->m_floor.set("11111111");
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
            m_data->machine.removeState();
    }
}

void GameState::update(float dt)
{
    m_floor->change_room("1");
    m_gui->update(dt);
    m_scientist.update(dt);
    m_shooter.update(dt);
    m_alien.update(dt);
}

void GameState::draw(float interpolation)
{
    m_data->wind.clear(sf::Color::Black);
    m_data->wind.draw(*this->m_floor->get_room());
    m_data->wind.draw(m_shooter);
    m_data->wind.draw(m_scientist);
    m_data->wind.draw(this->m_alien);
    m_gui->draw(interpolation);
    m_data->wind.display();
}
