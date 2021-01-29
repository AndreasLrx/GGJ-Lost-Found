/*
** EPITECH PROJECT, 2021
** GGI GUI
** File description:
** GUIAbstractTextShape
*/

#ifndef GUI_ABSTRACT_TEXT_SHAPE_H
#define GUI_ABSTRACT_TEXT_SHAPE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "GUI/TextItem.hpp"
#include "GUI/GUIItem.hpp"

class GUIAbstractTextShape :public TextItem, public GUIItem
{
        GUIAbstractTextShape();
        virtual ~GUIAbstractTextShape();

        virtual void clearUpdateTypes();

    protected:
        virtual void init(int nbStates, std::string str, sf::Font *font = nullptr, unsigned int charSize = 15);
        virtual void updateStateFull(void);
        virtual void updateState(void);
};

#endif /* !GUI_ABSTRACT_TEXT_SHAPE_H */