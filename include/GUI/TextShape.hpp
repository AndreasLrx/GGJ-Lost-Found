/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextShape
*/

#ifndef GUI_TEXT_SHAPE_H
#define GUI_TEXT_SHAPE_H

#include "GUI/GUIAbstractTextShape.hpp"

class TextShape :public TextItem, public GUIItem{
    public:
        TextShape() {};
        ~TextShape() {};

        void clearUpdateTypes();

        void setPosition(sf::Vector2f pos) {GUIItem::setPosition(pos);};
        void setPosition(float x, float y) {GUIItem::setPosition(x, y);};
        sf::Vector2f getPosition() {return GUIItem::getPosition();};

        void setTag(int tag) {GUIItem::setTag(tag);};
        int getTag() {return GUIItem::getTag();};
        void setData(GameDataRef data) {GUIItem::setData(data);};

    protected:
        void init(int nbStates, std::string str, sf::Font *font = nullptr, unsigned int charSize = 15);
        void updateStateFull(void);
        void updateState(void);
};

#endif /* !GUI_TEXT_SHAPE_H */