/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** RadioButtons
*/

#include "GUI/RadioButtons.hpp"
#include "GUI/CheckBox.hpp"

RadioButtons::RadioButtons(int nbButtons, sf::Vector2f pos, sf::Vector2f size, inputReactFct input, updateReactFct update)
{
    initShape(2);
    m_isVertical = 1;
    m_padding = 0;
    m_nbButtons = nbButtons;
    m_selected = 0;
    m_allocatedSize = nbButtons;
    m_buttons = new CheckBox*[nbButtons];
    for (int i = 0; i < nbButtons; i++)
        m_buttons[i] = new CheckBox(sf::Vector2f(pos.x, pos.y + size.y * i), size);
    m_buttons[0]->setSelected(CHECKED);
    m_inputReact = input;
    m_updateReact = update;
}

RadioButtons::~RadioButtons()
{
    clearShapeUpdateTypes();
    for (int i = 0; i < m_nbButtons; i++) {
        m_buttons[i]->m_updateTypes[0] = 0;
        delete m_buttons[i];
    }
    delete m_buttons;
}

void RadioButtons::addButton(int i)
{
    sf::Vector2f pos = m_buttons[0]->getPosition();
    sf::Vector2f size = m_buttons[0]->getSize();

    if (m_isVertical)
        m_buttons[i] = new CheckBox(sf::Vector2f(pos.x, pos.y + i * (size.y + m_padding)), size);
    else
        m_buttons[i] = new CheckBox(sf::Vector2f(pos.x + i * (size.x + m_padding), pos.y), size);
    m_buttons[i]->m_updateTypes[0] = m_buttons[0]->m_updateTypes[0];
    m_buttons[i]->m_fillColors[0] = m_buttons[0]->m_fillColors[0];
    m_buttons[i]->m_outColors[0] = m_buttons[0]->m_outColors[0];
    m_buttons[i]->m_textures[0] = m_buttons[0]->m_textures[0];
    m_buttons[i]->m_textureRects[0] = m_buttons[0]->m_textureRects[0];
    m_buttons[i]->updateShapeStateFull();
}

void RadioButtons::updateShapeStateFull()
{
    for (int i = 0; i < m_nbButtons; i++) {
        m_buttons[i]->m_updateTypes[0] = m_buttons[0]->m_updateTypes[0];
        m_buttons[i]->m_fillColors[0] = m_buttons[0]->m_fillColors[0];
        m_buttons[i]->m_outColors[0] = m_buttons[0]->m_outColors[0];
        m_buttons[i]->m_textures[0] = m_buttons[0]->m_textures[0];
        m_buttons[i]->m_textureRects[0] = m_buttons[0]->m_textureRects[0];
        m_buttons[i]->updateShapeStateFull();
    }
    updateShapeState();
}

void RadioButtons::updateShapeState(void)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->updateShapeState();
}

void RadioButtons::handleInput(sf::Event event)
{
    sf::Vector2i mousePos = m_data->input.getMousePosition(m_data->wind);
    int selected = m_selected;

    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left)
        return;
    for (int i = 0; i < m_nbButtons; i++) {
        if (m_buttons[i]->m_rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            selected = i;
    }
    if (selected != m_selected)
    {
        m_buttons[m_selected]->setSelected(NORMAL);
        m_selected = selected;
        m_buttons[m_selected]->setSelected(CHECKED);
        if (m_inputReact)
            m_inputReact(this, 0);
    }
}

void RadioButtons::update(float dt)
{
    if (dt)
        return;
}

void RadioButtons::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    for (int i = 0; i < m_nbButtons; i++)
        target.draw(*(m_buttons[i]), states);
}

void RadioButtons::setShapeColors(sf::Color fill, sf::Color outline, float outlineThickness)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->setShapeColors(fill, outline, outlineThickness);
}

void RadioButtons::setShapeOutlineThickness(float thickness)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->setShapeOutlineThickness(thickness);
}

int RadioButtons::getSelected()
{
    return m_selected;
}

void RadioButtons::setSelected(int id)
{
    if (id < 0 || id >= m_nbButtons || id == m_selected)
        return;
    m_buttons[m_selected]->setSelected(NORMAL);
    m_selected = id;
    m_buttons[m_selected]->setSelected(CHECKED);
}

void RadioButtons::setOrientation(int isVertical, float padding)
{
    if (m_isVertical == isVertical && abs(padding - m_padding) <= 0.001)
        return;
    m_isVertical = isVertical;
    m_padding = padding;
    setPosition(m_buttons[0]->getPosition());
}

int RadioButtons::isVertical()
{
    return m_isVertical;
}

float RadioButtons::getPadding()
{
    return m_padding;
}

int RadioButtons::getButtonCount()
{
    return m_nbButtons;
}

void RadioButtons::setButtonCount(int newCount)
{
    CheckBox **buttons = m_buttons;

    if (newCount <= 0 || newCount >= 50 || newCount == m_nbButtons)
        return;
    if (newCount < m_nbButtons) {
        for (int i = 0; i < (m_nbButtons - newCount); i++) {
            m_buttons[newCount + i]->m_updateTypes[0] = 0;
            delete m_buttons[newCount + i];
        }
    } else {
        if (newCount > m_allocatedSize) {
            m_buttons = new CheckBox*[newCount];
            for (int i = 0; i < m_nbButtons; i++)
                m_buttons[i] = buttons[i];
            delete buttons;
            m_allocatedSize = newCount;
        }
        for (int i = m_nbButtons; i < newCount; i++)
            addButton(i);
    }
    m_nbButtons = newCount;
}

void RadioButtons::setPosition(sf::Vector2f pos)
{
    sf::Vector2f size = m_buttons[0]->getSize();

    if (m_isVertical) {
        for (int i = 0; i < m_nbButtons; i++)
            m_buttons[i]->setPosition(pos.x, pos.y + i * (size.y + m_padding));
    } else {
        for (int i = 0; i < m_nbButtons; i++)
            m_buttons[i]->setPosition(pos.x + i * (size.x + m_padding), pos.y);
    }
}

void RadioButtons::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

sf::Vector2f RadioButtons::getPosition()
{
    return m_buttons[0]->getPosition();
}

void RadioButtons::setShapeFillColoredUpdate(sf::Color *colors, int shape)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->setShapeFillColoredUpdate(colors, shape);
}

void RadioButtons::setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->setShapeFillColoredUpdate(normal, clicked, shape);
}

void RadioButtons::setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape)
{
    for (int i = 0; i < m_nbButtons; i++)
        m_buttons[i]->setShapeFillColoredUpdate(normal, hover, clicked, shape);
}