/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** Button
*/

#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "GUI/GUIItem.hpp"

class Button : public GUIItem
{
    public:
        Button(sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(100, 100), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~Button();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        int isClicked(void);

        void setSize(sf::Vector2f size);
        void setSize(float width, float height);
        sf::Vector2f getSize();

        sf::Shape *getShape();

    protected:
        void setDataRec() {};

        sf::RectangleShape m_rect;
};

#endif /* !GUI_BUTTON_H */