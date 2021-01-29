/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextShape
*/

#include <iostream>
#include "GUI/TextShape.hpp"

void TextShape::clearUpdateTypes()
{
    GUIItem::clearShapeUpdateTypes();
    TextItem::clearTextUpdateType();
}

void TextShape::init(int nbStates, std::string str, sf::Font *font, unsigned int charSize)
{
    initShape(nbStates);
    initText(nbStates, str, font, charSize);
}

void TextShape::updateStateFull(void)
{
    updateShapeStateFull();
    updateTextStateFull();
}

void TextShape::updateState(void)
{
    updateShapeState();
    updateTextState();
}