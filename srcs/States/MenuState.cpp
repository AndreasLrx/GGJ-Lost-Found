/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** MenuState
*/

#include <iostream>
#include "States/MenuState.hpp"
#include "GUI/TextField.hpp"
#include "GUI/Button.hpp"
#include "GUI/CheckBox.hpp"
#include "GUI/RadioButtons.hpp"
#include "GUI/ScrollBar.hpp"
#include "GUI/TextButton.hpp"
#include "GUI/ClickableText.hpp"

MenuState::MenuState(GameDataRef data)
{
    m_data = data;
    m_gui = new GUIManager(data);

    Button *btn = new Button(sf::Vector2f(10, 10), sf::Vector2f(100, 100), \
    [](GUIAbstract *btn, int tag){std::cout<<"Button clicked"<<std::endl;});
    btn->setShapeTexturedRectUpdate(m_data->assets.getTexture("iceButtons"), sf::Vector2i(650, 0), sf::Vector2i(130, 130), 1);
    m_gui->addItem(btn, 0);
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
    m_data->wind.clear(sf::Color::Blue);
    m_gui->draw(interpolation);
    m_data->wind.display();
}