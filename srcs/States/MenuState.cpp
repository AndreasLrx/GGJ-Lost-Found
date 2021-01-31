/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** MenuState
*/

#include <iostream>
#include "States/MenuState.hpp"
#include "States/GameState.hpp"
#include "States/LevelSelectState.hpp"
#include "GUI/Button.hpp"
#include "GUI/TextButton.hpp"

MenuState::MenuState(GameDataRef data)
{
    m_data = data;
    sf::Vector2f backgroundSize(500 * SCL(this), 590 * SCL(this));
    m_gui = new GUIManager(data);
    m_background.setSize(backgroundSize);
    m_background.setTexture(m_data->assets.getTexture("menu"));
    m_background.setPosition((m_data->wind.getSize().x - backgroundSize.x) / 2.f,  (m_data->wind.getSize().y - backgroundSize.y) / 2.f);

    TextButton *playBtn = new TextButton("Play", m_data->assets.getFont("spincycle"), sf::Vector2f(0, 175 * SCL(this)), sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)), \
    [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.addState(StateRef(new GameState(btn->getData())), 0);
        btn->getData()->assets.stopMusic("menu_music");});
    playBtn->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 52, 165, 52}, {0, 52, 165, 52});
    playBtn->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    playBtn->setCharacterSize(30  * SCL(this));
    playBtn->setTextColors(sf::Color::Black);

    TextButton *tuto = new TextButton("Tutorial", m_data->assets.getFont("spincycle"), sf::Vector2f(0, 268 * SCL(this)), sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)), \
    [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.addState(StateRef(new LevelSelectState(btn->getData())), 0);});
    tuto->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 52, 165, 52}, {0, 52, 165, 52});
    tuto->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    tuto->setCharacterSize(30  * SCL(this));
    tuto->setTextColors(sf::Color::Black);

    TextButton *settings = new TextButton("Settings", m_data->assets.getFont("spincycle"), sf::Vector2f(0, 361 * SCL(this)), sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)));
    settings->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 52, 165, 52}, {0, 52, 165, 52});
    settings->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    settings->setCharacterSize(30  * SCL(this));
    settings->setTextColors(sf::Color::Black);

    TextButton *quit = new TextButton("Quit", m_data->assets.getFont("spincycle"), sf::Vector2f(0, 453 * SCL(this)), sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)), \
    [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->wind.close();});
    quit->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 52, 165, 52}, {0, 52, 165, 52});
    quit->center(m_data->wind.getSize(), sf::Vector2i(1, 0));
    quit->setCharacterSize(30  * SCL(this));
    quit->setTextColors(sf::Color::Black);

    m_gui->addItem(playBtn->getBase(), PLAY_BUTTON);
    m_gui->addItem(tuto->getBase(), TUTORIAL_BUTTON);
    m_gui->addItem(settings->getBase(), SETTINGS_BUTTON);
    m_gui->addItem(quit->getBase(), QUIT_BUTTON);
    m_data->assets.playMusic("menu_music");
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

void MenuState::draw(sf::RenderTarget& target, float interpolation)
{
    target.clear(sf::Color(100, 100, 100));
    target.draw(m_background);
    m_gui->draw(interpolation);
}