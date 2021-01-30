/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextButton
*/

#include "GUI/TextButton.hpp"

TextButton::TextButton(std::string str, sf::Font *font, sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update)
{
    initShape(3);
    initText(3, str, font);
    Button::m_inputReact = input;
    Button::m_updateReact = update;
    m_rect.setPosition(pos);
    m_rect.setSize(size);
    Button::addShape(&m_rect);
    m_text.setPosition(pos);
    replaceText();
}

TextButton::~TextButton()
{
    clearShapeUpdateTypes();
    clearTextUpdateType();
}

void TextButton::center(sf::Vector2u windSize, sf::Vector2i needCenter)
{
    Button::center(windSize, needCenter);
    replaceText();
}

void TextButton::setString(std::string str)
{
    sf::FloatRect localBounds;

    m_text.setString(str);
    replaceText();
}

void TextButton::setCharacterSize(unsigned int size)
{
    TextItem::setCharacterSize(size);
    replaceText();
}

void TextButton::replaceText()
{
    sf::FloatRect localBounds = m_text.getLocalBounds();
    sf::FloatRect buttonBounds = m_rect.getGlobalBounds();

    m_text.setOrigin(localBounds.left, localBounds.top);
    m_text.setPosition(buttonBounds.left - (localBounds.width - buttonBounds.width) / 2.f, \
    buttonBounds.top - (localBounds.height - buttonBounds.height) / 2.f);
}

void TextButton::handleInput(sf::Event event)
{
    int state = Button::m_state;

    Button::handleInput(event);
    if (Button::m_state != state) {
        TextItem::m_state = Button::m_state;
        updateTextState();
    }
}

void TextButton::update(float dt)
{
    if (dt)
        return;
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_rect, states);
    target.draw(m_text, states);
}

void TextButton::setPosition(sf::Vector2f pos)
{
    Button::setPosition(pos);
}

void TextButton::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

sf::Vector2f TextButton::getPosition()
{
    return Button::getPosition();
}