/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextItem
*/

#include <iostream>
#include "GUI/TextItem.hpp"

void TextItem::initText(int nbStates, std::string str, sf::Font *font, unsigned int charSize)
{
    m_state = 0;
    m_nbStates = nbStates;
    m_textUpdateTypes = 0;
    m_font = font;
    m_charSize = charSize;
    m_text.setFont(*font);
    m_text.setCharacterSize(charSize);
    setString(str);
}

void TextItem::updateTextStateFull()
{
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Transparent);
    if (m_textUpdateTypes & TEXT_COLORED)
        m_text.setFillColor(m_textFillColors[m_state]);
    if (m_textUpdateTypes & TEXT_OUT_COLORED)
        m_text.setOutlineColor(m_textOutColors[m_state]);
    updateTextState();
}

void TextItem::updateTextState(void)
{
    if (m_textUpdateTypes & TEXT_COLORED)
        m_text.setFillColor(m_textFillColors[m_state]);
    if (m_textUpdateTypes & TEXT_OUT_COLORED)
        m_text.setOutlineColor(m_textOutColors[m_state]);
}

std::string TextItem::getString(void)
{
    return m_text.getString().toAnsiString();
}

void TextItem::setString(std::string str)
{
    m_text.setString(str);
}

void TextItem::setTextColors(sf::Color fill, sf::Color outline, float outlineThickness)
{
    m_text.setFillColor(fill);
    m_text.setOutlineColor(outline);
    m_text.setOutlineThickness(outlineThickness);
}

void TextItem::setTextOutlineThickness(float outlineThickness)
{
    m_text.setOutlineThickness(outlineThickness);
}

void TextItem::setTextParams(sf::Font *font, unsigned int charSize)
{
    if (font != nullptr) {
        m_font = font;
        m_text.setFont(*font);
    }
    if (charSize == 0)
        return;
    m_charSize = charSize;
    m_text.setCharacterSize(charSize);
}

void TextItem::setCharacterSize(unsigned int charSize)
{
    setTextParams(nullptr, charSize);
}

void TextItem::setFont(sf::Font *font)
{
    setTextParams(font);
}

void TextItem::clearTextUpdateType(void)
{
    if (m_textUpdateTypes & TEXT_COLORED)
        delete m_textFillColors;
    if (m_textUpdateTypes & TEXT_OUT_COLORED)
        delete m_textOutColors;
    updateTextStateFull();
}

void TextItem::setTextFillColoredUpdate(sf::Color *colors)
{
    m_textUpdateTypes |= TEXT_COLORED;
    m_textFillColors = colors;
    updateTextStateFull();
}

void TextItem::setTextFillColoredUpdate(sf::Color normal, sf::Color clicked)
{
    sf::Color *colors = new sf::Color[2];

    colors[0] = normal;
    colors[1] = clicked;
    setTextFillColoredUpdate(colors);
}

void TextItem::setTextFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked)
{
    sf::Color *colors = new sf::Color[3];

    colors[0] = normal;
    colors[1] = hover;
    colors[2] = clicked;
    setTextFillColoredUpdate(colors);
}

void TextItem::setTextOutColoredUpdate(sf::Color *colors)
{
    m_textUpdateTypes |= TEXT_OUT_COLORED;
    m_textOutColors = colors;
    updateTextStateFull();
}

void TextItem::setTextOutColoredUpdate(sf::Color normal, sf::Color clicked)
{
    sf::Color *colors = new sf::Color[2];

    colors[0] = normal;
    colors[1] = clicked;
    setTextOutColoredUpdate(colors);
}

void TextItem::setTextOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked)
{
    sf::Color *colors = new sf::Color[3];

    colors[0] = normal;
    colors[1] = hover;
    colors[2] = clicked;
    setTextOutColoredUpdate(colors);
}