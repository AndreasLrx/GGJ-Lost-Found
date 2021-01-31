/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** GamePauseState
*/

#include "States/GamePauseState.hpp"
#include "GUI/TextButton.hpp"
#include <iostream>

GamePauseState::GamePauseState(GameDataRef data)
{
    m_data = data;
    sf::Vector2f backgroundSize(500 * SCL(this), 590 * SCL(this));
    m_gui = new GUIManager(data);
    m_menu.setSize(backgroundSize);
    m_menu.setTexture(m_data->assets.getTexture("menu"));
    m_menu.setPosition((m_data->wind.getSize().x - backgroundSize.x) / 2.f,  (m_data->wind.getSize().y - backgroundSize.y) / 2.f);

    initBtn("Resume", sf::Vector2f(525 * SCL(this), 265 * SCL(this)), 0, [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.removeState();});
    initBtn("Home", sf::Vector2f(525 * SCL(this), 368 * SCL(this)), 1, [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.removeStates(2);});
    m_texture.create(1280, 720);
    m_data->machine.GetActiveState()->draw(m_texture, 0);
    m_texture.display();
    m_background.setSize(sf::Vector2f(1280, 720));
    m_background.setTexture(&m_texture.getTexture());
    m_background.setFillColor(sf::Color(120, 120, 120, 220));
}

GamePauseState::~GamePauseState()
{
    delete m_gui;
}

void GamePauseState::initBtn(std::string text, sf::Vector2f pos, int tag, inputReactFct input)
{
    TextButton *btn = new TextButton(text, m_data->assets.getFont("spincycle"), pos, sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)), input);
    btn->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 0, 165, 52}, {0, 52, 165, 52});
    btn->setCharacterSize(30  * SCL(this));
    btn->setTextFillColoredUpdate(sf::Color(205, 240, 238), sf::Color(247, 239, 201), sf::Color(247, 239, 201));

    m_gui->addItem(btn->getBase(), tag);
}

void GamePauseState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            m_data->machine.removeState();
        m_gui->handleInput(event);
    }
}

void GamePauseState::update(float dt)
{
    m_gui->update(dt);
}

void GamePauseState::draw(sf::RenderTarget& target, float interpolation)
{
    target.clear(sf::Color(130, 130, 130));
    target.draw(m_background);
    target.draw(m_menu);
    m_gui->draw(interpolation);        
}