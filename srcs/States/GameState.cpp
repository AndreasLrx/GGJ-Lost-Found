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
    this->m_projectile = nullptr;
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
    this->m_floor = new Floor(this->m_data, &m_alien);
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
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
            m_data->assets.stopMusic("battletheme");
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
            m_data->assets.playMusic("battletheme");
        }
    }
}

void GameState::update(float dt)
{
    m_floor->change_room(dt, "1");
    m_gui->update(dt);
    m_alien.update(dt);
    if (this->m_projectile != nullptr)
        this->m_projectile->update(dt);
}

void GameState::draw(float interpolation)
{
    m_data->wind.clear(sf::Color::Black);
    m_data->wind.draw(*this->m_floor->get_room());
    m_data->wind.draw(this->m_alien);
    if (this->m_projectile != nullptr)
        m_data->wind.draw(*this->m_projectile);
    m_gui->draw(interpolation);
    m_data->wind.display();
}

void GameState::spawnProjectile(AbstractProjectile* projectile, Entity* owner)
{
    if (this->m_projectile != nullptr)
        delete this->m_projectile;
    this->m_projectile = projectile;
    projectile->spawn(owner, m_data);
}
