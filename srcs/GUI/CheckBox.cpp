/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** CheckBox
*/

#include <iostream>
#include "GUI/CheckBox.hpp"

CheckBox::CheckBox(sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update) : Button(pos, size)
{
    m_nbStates = 2;
    m_inputReact = input;
    m_updateReact = update;
}

CheckBox::~CheckBox()
{
    clearShapeUpdateTypes();
}

void CheckBox::handleInput(sf::Event event)
{
    sf::Vector2i mousePos = m_data->input.getMousePosition(m_data->wind);
    int inRect = m_rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
    int clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (event.type != sf::Event::MouseButtonPressed)
        return;
    if (inRect && clicked)
        setSelected(!m_state);
}

void CheckBox::setSelected(bool isSelected)
{
    m_state = isSelected;
    updateShapeState();
    if (m_inputReact)
        m_inputReact(this, 0);
}

bool CheckBox::isSelected(void)
{
    return (m_state == CHECKED);
}