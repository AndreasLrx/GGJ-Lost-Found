/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIItem
*/

#include <iostream>
#include "GUI/GUIItem.hpp"

void GUIItem::initShape(int nbStates)
{
    m_nbStates = nbStates;
    m_updateTypes.clear();
    m_state = 0;
    m_shapes.clear();
}

void GUIItem::addShape(sf::Shape *shape)
{
    m_shapes.push_back(shape);
    m_updateTypes.push_back(0);
    m_fillColors.push_back(nullptr);
    m_outColors.push_back(nullptr);
    m_textures.push_back(nullptr);
    m_textureRects.push_back(nullptr);
}

void GUIItem::updateShapeStateFull(void)
{
    for (size_t i = 0; i < m_shapes.size(); i++) {
        if (m_shapes[i] == nullptr)
            continue;
        m_shapes[i]->setFillColor(sf::Color::White);
        m_shapes[i]->setOutlineColor(sf::Color::Transparent);
        if (m_updateTypes[i] & (TEXTURED_RECT | TEXTURED)) {
            m_shapes[i]->setTexture((m_updateTypes[i] & TEXTURED) ? (m_textures[i][m_state]) : m_textures[i][0], true);
            if (m_updateTypes[i] & TEXTURED_RECT)
                m_shapes[i]->setTextureRect(m_textureRects[i][0]);
        }
        else
            m_shapes[i]->setTexture(NULL, true);
        if (m_updateTypes[i] & COLOR)
            m_shapes[i]->setFillColor(m_fillColors[i][m_state]);
        if (m_updateTypes[i] & OUT_COLORED)
            m_shapes[i]->setOutlineColor(m_outColors[i][m_state]);
    }
    updateShapeState();
}

void GUIItem::updateShapeState(void)
{
    for (size_t i = 0; i < m_shapes.size(); i++) {
        if (m_shapes[i] == nullptr)
            continue;
        if (m_updateTypes[i] & COLOR)
            m_shapes[i]->setFillColor(m_fillColors[i][m_state]);
        if (m_updateTypes[i] & OUT_COLORED)
            m_shapes[i]->setOutlineColor(m_outColors[i][m_state]);
        if (m_updateTypes[i] & TEXTURED)
            m_shapes[i]->setTexture(m_textures[i][m_state], true);
        if (m_updateTypes[i] & TEXTURED_RECT)
            m_shapes[i]->setTextureRect(m_textureRects[i][m_state]);
    }
}

void GUIItem::setShapeColors(sf::Color fill, sf::Color outline, float outlineThickness, int shape)
{
    m_shapes[shape]->setFillColor(fill);
    m_shapes[shape]->setOutlineColor(outline);
    setShapeOutlineThickness(outlineThickness, shape);
}

void GUIItem::setShapeOutlineThickness(float thickness, int shape)
{
    m_shapes[shape]->setOutlineThickness(thickness);
}

void GUIItem::clearShapeUpdateTypes(int shape)
{
    if (shape != -1)
        clearShapeUpdateType(shape);
    else {
        for (size_t i = 0; i < m_shapes.size(); i++)
            clearShapeUpdateType(i);
    }
    updateShapeStateFull();
}

void GUIItem::clearShapeUpdateType(int shape)
{
    if (m_shapes[shape] == nullptr)
            return;
    if (m_updateTypes[shape] & COLOR)
        delete m_fillColors[shape];
    if (m_updateTypes[shape] & OUT_COLORED)
        delete m_outColors[shape];
    if (m_updateTypes[shape] & (TEXTURED | TEXTURED_RECT))
        delete m_textures[shape];
    if (m_updateTypes[shape] & TEXTURED_RECT)
        delete m_textureRects[shape];
}

void GUIItem::setShapeFillColoredUpdate(sf::Color *colors, int shape)
{
    m_updateTypes[shape] |= COLOR;
    m_fillColors[shape] = colors;
    updateShapeStateFull();
}

void GUIItem::setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape)
{
    sf::Color *colors = new sf::Color[2];

    colors[0] = normal;
    colors[1] = clicked;
    setShapeFillColoredUpdate(colors, shape);
}

void GUIItem::setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape)
{
    sf::Color *colors = new sf::Color[3];

    colors[0] = normal;
    colors[1] = hover;
    colors[2] = clicked;
    setShapeFillColoredUpdate(colors, shape);
}

void GUIItem::setShapeOutColoredUpdate(sf::Color *colors, int shape)
{
    m_updateTypes[shape] |= OUT_COLORED;
    m_outColors[shape] = colors;
    updateShapeStateFull();
}

void GUIItem::setShapeOutColoredUpdate(sf::Color normal, sf::Color clicked, int shape)
{
    sf::Color *colors = new sf::Color[2];

    colors[0] = normal;
    colors[1] = clicked;
    setShapeOutColoredUpdate(colors, shape);
}

void GUIItem::setShapeOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape)
{
    sf::Color *colors = new sf::Color[3];

    colors[0] = normal;
    colors[1] = hover;
    colors[2] = clicked;
    setShapeOutColoredUpdate(colors, shape);
}

void GUIItem::setShapeTexturedUpdate(sf::Texture **textures, int shape)
{
    m_updateTypes[shape] |= TEXTURED;
    if (m_updateTypes[shape] & TEXTURED_RECT) {
        delete m_textures[shape];
        m_updateTypes[shape] -= TEXTURED_RECT;
    }
    m_textures[shape] = textures;
    updateShapeStateFull();
}

void GUIItem::setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &clicked, int shape)
{
    sf::Texture **textures = new sf::Texture*[2];

    textures[0] = &normal;
    textures[1] = &clicked;
    setShapeTexturedUpdate(textures, shape);
}

void GUIItem::setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &hover, sf::Texture &clicked, int shape)
{
    sf::Texture **textures = new sf::Texture*[3];

    textures[0] = &normal;
    textures[1] = &hover;
    textures[2] = &clicked;
    setShapeTexturedUpdate(textures, shape);
}

void GUIItem::setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect *rects, int shape)
{
    m_updateTypes[shape] |= TEXTURED_RECT;
    if (m_updateTypes[shape] & TEXTURED) {
        delete m_textures[shape];
        m_updateTypes[shape] -= TEXTURED;
    }
    m_textures[shape] = new sf::Texture*[1];
    m_textures[shape][0] = texture;
    m_textureRects[shape] = rects;
    updateShapeStateFull();
}

void GUIItem::setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect clicked, int shape)
{
    sf::IntRect *rects = new sf::IntRect[2];

    rects[0] = normal;
    rects[1] = clicked;
    setShapeTexturedRectUpdate(texture, rects, shape);
}

void GUIItem::setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect hover, sf::IntRect clicked, int shape)
{
    sf::IntRect *rects = new sf::IntRect[3];

    rects[0] = normal;
    rects[1] = hover;
    rects[2] = clicked;
    setShapeTexturedRectUpdate(texture, rects, shape);
}

void GUIItem::setShapeTexturedRectUpdate(sf::Texture *texture, sf::Vector2i start, sf::Vector2i size, int isVertical, int shape)
{
    sf::IntRect *rects = new sf::IntRect[m_nbStates];
    sf::Vector2i pos = start;

    for (int i = 0; i < m_nbStates; i++) {
        rects[i] = sf::IntRect(pos, size);
        if (isVertical)
            pos.y += size.y;
        else
            pos.x += size.x;
    }
    setShapeTexturedRectUpdate(texture, rects, shape);
}

void GUIItem::setPosition(sf::Vector2f pos)
{
    m_shapes[0]->setPosition(pos);
}

void GUIItem::setPosition(float x, float y)
{
    m_shapes[0]->setPosition(x, y);
}
        
sf::Vector2f GUIItem::getPosition()
{
    return m_shapes[0]->getPosition();
}