/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** ScrollBar
*/

#ifndef GUI_SCROLLBAR_H
#define GUI_SCROLLBAR_H

#include "GUI/GUIItem.hpp"

class Button;

class ScrollBar : public GUIItem
{
    public:
        enum SHAPES {BAR, CURSOR};

        ScrollBar(sf::Vector2f cursorSize = sf::Vector2f(20, 10), sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(10, 400), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~ScrollBar();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        void setValue(float value);
        float getValue();
        void setMinMax(sf::Vector2f minMax);
        void setOrientation(int isVertical);

    protected:
        void setCursorPos(float pos);
        void setDataRec();

        int m_isVertical;
        Button *m_cursor;
        float m_maxDiff;
        sf::RectangleShape m_bar;
        sf::Vector2f m_minMax;
};

#endif /* !GUI_SCROLLBAR_H */