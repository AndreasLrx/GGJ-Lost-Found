/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** Buttons
*/

#include <iostream>
#include "GUI/Button.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update)
{
    initShape(3);
    m_inputReact = input;
    m_updateReact = update;
    m_rect.setPosition(pos);
    m_rect.setSize(size);
    addShape(&m_rect);
}

Button::~Button()
{
    clearShapeUpdateTypes();
}

void Button::center(sf::Vector2u windSize, sf::Vector2i needCenter)
{
    sf::Vector2f size = m_rect.getSize();
    sf::Vector2f newPos = m_rect.getPosition();

    if (needCenter.x)
        newPos.x = (windSize.x - size.x) / 2;
    if (needCenter.y)
        newPos.y = (windSize.y - size.y) / 2;
    m_rect.setPosition(newPos);
}

void Button::handleInput(sf::Event event)
{
    sf::Vector2i mousePos = m_data->input.getMousePosition(m_data->wind);
    int inRect = m_rect.getGlobalBounds().contains(mousePos.x, mousePos.y);
    int clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    int state = m_state;
    int wasClicked = isClicked();

    if (event.type != sf::Event::MouseMoved && event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased)
        return;
    if (clicked && m_state == CLICKED)
        return;
    if (inRect)
        m_state = (clicked) ? CLICKED : HOVER;
    else
        m_state = NORMAL;
    if (m_nbStates == 2)
        m_state -= (m_state > 0);
    if (state != m_state) {
        updateShapeState();
        if (wasClicked && m_inputReact)
            m_inputReact(this, 0);
    }    
}

void Button::update(float dt)
{
    if (dt)
        return;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_rect, states);
}

void Button::setSize(sf::Vector2f size)
{
    m_rect.setSize(size);
}

void Button::setSize(float width, float height)
{
    setSize(sf::Vector2f(width, height));
}

sf::Vector2f Button::getSize()
{
    return m_rect.getSize();
}

int Button::isClicked(void)
{
    return (m_state == CLICKED || (m_state == HOVER && m_state == 2));
}

sf::Shape *Button::getShape()
{
    return &m_rect;
}