/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextField
*/

#include <iostream>
#include "GUI/CheckBox.hpp"
#include "GUI/TextField.hpp"

TextField::TextField(sf::Font *font, std::string text, sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update)
{
    m_rect = new CheckBox(pos, size);
    init(2, text, font);    
    GUIItem::m_inputReact = input;
    GUIItem::m_updateReact = update;
    m_cursor = text.size();
    m_cursorClock = 0;
    m_whitelist.clear();
    m_str = text;
    m_text.setPosition(pos);
    setString(m_str);
}

void TextField::setDataRec()
{
    m_rect->setData(GUIItem::m_data);
}

TextField::~TextField()
{
    clearUpdateTypes();
    m_rect->m_updateTypes[0] = 0;
    delete m_rect;
}

void TextField::updateStateFull()
{
    updateTextStateFull();
    m_rect->m_updateTypes = m_updateTypes;
    m_rect->m_fillColors = m_fillColors;
    m_rect->m_outColors = m_outColors;
    m_rect->m_textures = m_textures;
    m_rect->m_textureRects = m_textureRects;
    m_rect->updateShapeStateFull();
}

void TextField::updateState(void)
{
    updateTextState();
    m_rect->updateShapeState();
}

void TextField::handleText(sf::Uint32 unicode)
{
    switch (unicode) {
    case 8:
        if (m_cursor > 0)
            m_str.erase(--m_cursor, 1);
        break;
    case 13:
        if (GUIItem::m_inputReact)
            GUIItem::m_inputReact(static_cast<GUIItem *>(this), 0);
        break;
    case 27:
        m_rect->setSelected(NORMAL);
        break;
    default:
        if (m_whitelist.size() == 0 || m_whitelist.find(unicode) != std::string::npos) {
            m_str.insert(m_cursor, 1, unicode);
            m_cursor++;
        }
        break;
    }
    setString(m_str);
}

void TextField::moveCursor(sf::Keyboard::Key key)
{
    if (key != sf::Keyboard::Left && key != sf::Keyboard::Right)
        return;
    if (key == sf::Keyboard::Left && m_cursor > 0)
        m_cursor--;
    if (key == sf::Keyboard::Right && static_cast<long unsigned int>(m_cursor) < m_str.size())
        m_cursor++;
}

void TextField::handleInput(sf::Event event)
{
    int selected = m_rect->isSelected();

    m_rect->handleInput(event);
    if (selected != m_rect->isSelected()) {
        GUIItem::m_state = m_rect->isSelected();
        updateTextState();
    }   
    if (selected) {
        if (event.type == sf::Event::TextEntered)
            handleText(event.text.unicode);
        if (event.type == sf::Event::KeyPressed)
            moveCursor(event.key.code);
    }
}

void TextField::update(float dt)
{
    m_cursorClock += dt;
    if (m_cursorClock >= 1.f) {
        m_cursorClock = 0;
    }
}

void TextField::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(*m_rect);
    target.draw(m_text);
    if (m_rect->isSelected() && m_cursorClock > 0.5f) {
        sf::Color color = m_text.getFillColor();
        sf::Vector2f pos = m_text.findCharacterPos(m_cursor);
        float height = m_charSize;
        sf::Vertex cursor[] = {
            sf::Vertex(sf::Vector2f(pos.x, pos.y + height * 0.1f), color),
            sf::Vertex(sf::Vector2f(pos.x, pos.y + height * 1.1f), color)
        };
        target.draw(cursor, 2, sf::Lines, states);
    }
}

std::string TextField::getString(void)
{
    return m_str;
}

void TextField::setString(std::string str)
{
    sf::FloatRect textBounds;
    sf::FloatRect bounds = m_rect->m_rect.getGlobalBounds();
    int rightMax = bounds.left + bounds.width;

    m_str = str;
    m_text.setString(str);
    textBounds = m_text.getGlobalBounds();
    if (static_cast<long unsigned int>(m_cursor) >= m_str.size())
        m_cursor = m_str.size();
    while (m_str.size() > 0 && textBounds.left + textBounds.width > rightMax) {
        m_str.erase(--m_cursor, 1);
        m_text.setString(m_str);
        textBounds = m_text.getGlobalBounds();
    }
}

std::string TextField::getWhitelist(void)
{
    return m_whitelist;
}

void TextField::setWhitelist(std::string whitelist)
{
    m_whitelist = whitelist;
}

int TextField::isSelected()
{
    return m_rect->isSelected();
}

void TextField::setSelected(int selected)
{
    m_rect->setSelected(selected);
}

void TextField::setShapeFillColoredUpdate(sf::Color *colors, int shape)
{
    m_rect->setShapeFillColoredUpdate(colors, shape);
}

void TextField::setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape)
{
    m_rect->setShapeFillColoredUpdate(normal, clicked, shape);
}

void TextField::setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape)
{
    m_rect->setShapeFillColoredUpdate(normal, hover, clicked, shape);
}

void TextField::setShapeColors(sf::Color fill, sf::Color outline, float outlineThickness)
{
    m_rect->setShapeColors(fill, outline, outlineThickness);
}

void TextField::setShapeOutlineThickness(float thickness)
{
    m_rect->setShapeOutlineThickness(thickness);
}