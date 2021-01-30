/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** Scrollbar
*/

#include <iostream>
#include <algorithm>
#include "GameEngine/Core.hpp"
#include "GUI/ScrollBar.hpp"
#include "GUI/Button.hpp"

ScrollBar::ScrollBar(sf::Vector2f cursorSize, sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update)
{
    initShape(3);
    m_inputReact = input;
    m_updateReact = update;
    m_bar.setPosition(pos);
    m_bar.setSize(size);
    addShape(&m_bar);
    m_isVertical = 1;
    m_minMax = sf::Vector2f(0, 100);
    m_cursor = new Button(sf::Vector2f(pos.x - (cursorSize.x - size.x) / 2.f, pos.y), cursorSize);
    m_cursor->setShapeColors(sf::Color::Black);
    m_maxDiff = size.y - cursorSize.y;
    addShape(m_cursor->getShape());
}

ScrollBar::~ScrollBar()
{
    clearShapeUpdateTypes();
}

void ScrollBar::setDataRec()
{
    m_cursor->setData(m_data);
}

void ScrollBar::setCursorPos(float pos)
{
    sf::Vector2f cursPos = m_cursor->getPosition();
    sf::FloatRect barBounds = m_bar.getGlobalBounds();

    if (m_isVertical)
        cursPos.y = std::max(barBounds.top, std::min(pos, barBounds.top + barBounds.height - m_cursor->getSize().y));
    else
        cursPos.x = std::max(barBounds.left, std::min(pos, barBounds.left + barBounds.width - m_cursor->getSize().x));
    m_cursor->setPosition(cursPos);
}

void ScrollBar::handleInput(sf::Event event)
{
    int clicked = m_cursor->isClicked();
    int state = m_cursor->getState();

    m_cursor->handleInput(event);
    if (state != m_cursor->getState()) {
        m_state = m_cursor->getState();
        updateShapeState();
        if (clicked && m_inputReact)
            m_inputReact(this, 0);
    }   
    if (m_cursor->isClicked()) {
        if (event.type == sf::Event::MouseMoved)
            setCursorPos((m_isVertical) ? event.mouseMove.y : event.mouseMove.x);
    }
}

void ScrollBar::update(float dt)
{
    if (dt)
        return;
}

void ScrollBar::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_bar, states);
    target.draw(*m_cursor, states);
}

void ScrollBar::setValue(float value)
{
    sf::FloatRect barBounds = m_bar.getGlobalBounds();
    sf::FloatRect cursorBounds = m_cursor->getShape()->getGlobalBounds();
    sf::Vector2f pos(cursorBounds.left, cursorBounds.top);
    float diff;

    value = std::max(m_minMax.x, std::min(value, m_minMax.y));
    diff = m_maxDiff * (value - m_minMax.x) / (m_minMax.y - m_minMax.x);
    if (m_isVertical)
        pos.y = diff + barBounds.top;
    else
        pos.x = diff + barBounds.left;
    m_cursor->setPosition(pos);
}

float ScrollBar::getValue()
{
    sf::FloatRect barBounds = m_bar.getGlobalBounds();
    sf::FloatRect cursorBounds = m_cursor->getShape()->getGlobalBounds();
    float diff;
    float value;

    if (m_isVertical)
        diff = cursorBounds.top - barBounds.top;
    else
        diff = cursorBounds.left - barBounds.left;
    value = m_minMax.x + (m_minMax.y - m_minMax.x) * (diff / m_maxDiff);
    return value;
}

void ScrollBar::setMinMax(sf::Vector2f minMax)
{
    m_minMax = minMax;
}

void ScrollBar::setOrientation(int isVertical)
{
    sf::Vector2f barPos = m_bar.getPosition();
    sf::Vector2f barSize = m_bar.getSize();
    sf::Vector2f cursorSize = m_cursor->getSize();
    float value = getValue();

    if (m_isVertical == isVertical)
        return;
    m_isVertical = isVertical;
    if (m_isVertical) {
        m_maxDiff = barSize.y - cursorSize.y;
        m_cursor->setPosition(barPos.x - (cursorSize.x - barSize.x) / 2.f, 0);
    } else {
        m_maxDiff = barSize.x - cursorSize.x;
        m_cursor->setPosition(0, barPos.y - (cursorSize.y - barSize.y) / 2.f);
    }
    setValue(value);
}