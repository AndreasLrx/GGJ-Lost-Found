/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GameEndState
*/

#include "States/GameEndState.hpp"
#include "GUI/TextButton.hpp"
#include <iostream>

static float const TRANSITION_TIME = 1.5f;

GameEndState::GameEndState(GameDataRef data)
{
    m_data = data;
    m_endBackground.setSize(sf::Vector2f(1280 * SCL(this), 720 * SCL(this)));
    m_endReady = true;
    if (m_data->datas == 1) {
        m_endReady = false;
        m_endBackground.setTexture(m_data->assets.getTexture("game_end_win"));
    } else
        m_endBackground.setTexture(m_data->assets.getTexture("game_end_lose"));
    m_endBackground.setFillColor(sf::Color::Transparent);

    m_texture.create(1280, 720);
    m_data->machine.GetActiveState()->draw(m_texture, 0);
    m_texture.display();
    m_backgroundInit.setSize(sf::Vector2f(1280 * SCL(this), 720 * SCL(this)));
    m_backgroundInit.setTexture(&m_texture.getTexture());
    m_timer = 0;
}

GameEndState::~GameEndState()
{
    delete m_gui;
}

void GameEndState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Space && m_timer > TRANSITION_TIME)) {
            if (!m_endReady) {
                m_endReady = true;
                m_endBackground.setTexture(m_data->assets.getTexture("game_end_win2"));
            } else
                m_data->machine.removeStates(2);
        }
            
    }
}

void GameEndState::update(float dt)
{
    if (m_timer < TRANSITION_TIME) {
        m_timer += dt;
        m_endBackground.setFillColor(sf::Color(255, 255, 255, 255 * (m_timer / TRANSITION_TIME)));
        m_backgroundInit.setFillColor(sf::Color(255, 255, 255, 255 - 255 * (m_timer / TRANSITION_TIME)));
        if (m_timer >= TRANSITION_TIME)
            m_endBackground.setFillColor(sf::Color::White);
    }
}

void GameEndState::draw(sf::RenderTarget& target, float interpolation)
{
    target.clear(sf::Color(130, 130, 130));
    target.draw(m_backgroundInit);
    target.draw(m_endBackground);
}