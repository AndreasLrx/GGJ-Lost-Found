/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** ClickableText
*/

#include "GUI/ClickableText.hpp"

ClickableText::ClickableText(std::string str, sf::Font *font, sf::Vector2f pos, \
unsigned int charSize, inputReactFct input, updateReactFct update)
{
    initText(3, str, font, charSize);
    m_inputReact = input;
    m_updateReact = update;
    m_text.setPosition(pos);
}

ClickableText::~ClickableText()
{
    clearTextUpdateType();
}

void ClickableText::handleInput(sf::Event event)
{
    sf::Vector2i mousePos = m_data->input.getMousePosition(m_data->wind);
    int inRect = m_text.getGlobalBounds().contains(mousePos.x, mousePos.y);
    int clicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    int state = m_state;

    if (clicked && m_state == CLICKED)
        return;
    if (inRect)
        m_state = (clicked) ? CLICKED : HOVER;
    else
        m_state = NORMAL;
    if (m_nbStates == 2)
        m_state -= (m_state > 0);
    if (state != m_state) {
        updateTextState();
        if ((m_state == CLICKED || (m_state == HOVER && m_nbStates == 2)) && m_inputReact)
            m_inputReact(this, 0);
    }    
}

void ClickableText::update(float dt)
{

}

void ClickableText::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_text);
}

int ClickableText::isClicked(void)
{
    return (m_state == CLICKED || (m_state == HOVER && m_state == 2));
}

void ClickableText::setPosition(sf::Vector2f pos)
{
    m_text.setPosition(pos);
}

void ClickableText::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
}

sf::Vector2f ClickableText::getPosition()
{
    return m_text.getPosition();
}