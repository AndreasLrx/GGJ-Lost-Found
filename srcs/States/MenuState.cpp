/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** MenuState
*/

#include <iostream>
#include "States/MenuState.hpp"
#include "States/GameState.hpp"
#include "GUI/Button.hpp"
#include "GUI/TextButton.hpp"

MenuState::MenuState(GameDataRef data)
{
    m_data = data;
    m_gui = new GUIManager(data);


    TextButton *playBtn = new TextButton("Play", m_data->assets.getFont("roboto"), sf::Vector2f(0, 200 * SCL(this)), sf::Vector2f(200  * SCL(this), 50  * SCL(this)), \
    [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.addState(StateRef(new GameState(btn->getData())), 0);});
    playBtn->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    playBtn->setCharacterSize(30  * SCL(this));
    playBtn->setShapeFillColoredUpdate(sf::Color::White, sf::Color::Cyan, sf::Color::Blue);
    playBtn->setTextColors(sf::Color::Black);

    TextButton *tuto = new TextButton("Tutorial", m_data->assets.getFont("roboto"), sf::Vector2f(0, 300 * SCL(this)), sf::Vector2f(200  * SCL(this), 50  * SCL(this)));
    tuto->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    tuto->setCharacterSize(30  * SCL(this));
    tuto->setShapeFillColoredUpdate(sf::Color::White, sf::Color::Cyan, sf::Color::Blue);
    tuto->setTextColors(sf::Color::Black);

    TextButton *settings = new TextButton("Settings", m_data->assets.getFont("roboto"), sf::Vector2f(0, 400 * SCL(this)), sf::Vector2f(200  * SCL(this), 50  * SCL(this)));
    settings->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    settings->setCharacterSize(30  * SCL(this));
    settings->setShapeFillColoredUpdate(sf::Color::White, sf::Color::Cyan, sf::Color::Blue);
    settings->setTextColors(sf::Color::Black);

    TextButton *quit = new TextButton("Quit", m_data->assets.getFont("roboto"), sf::Vector2f(0, 500 * SCL(this)), sf::Vector2f(200  * SCL(this), 50  * SCL(this)), \
    [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->wind.close();});
    quit->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    quit->setCharacterSize(30  * SCL(this));
    quit->setShapeFillColoredUpdate(sf::Color::White, sf::Color::Cyan, sf::Color::Blue);
    quit->setTextColors(sf::Color::Black);

    m_gui->addItem(playBtn->getBase(), PLAY_BUTTON);
    m_gui->addItem(tuto->getBase(), TUTORIAL_BUTTON);
    m_gui->addItem(settings->getBase(), SETTINGS_BUTTON);
    m_gui->addItem(quit->getBase(), QUIT_BUTTON);
}

MenuState::~MenuState()
{
    delete m_gui;
}

void MenuState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        m_gui->handleInput(event);
    }
}

void MenuState::update(float dt)
{
    m_gui->update(dt);
}

void MenuState::draw(float interpolation)
{
    m_data->wind.clear(sf::Color::Black);
    m_gui->draw(interpolation);
    m_data->wind.display();
}