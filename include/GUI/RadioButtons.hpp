/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** RadioButton
*/

#ifndef GUI_RADIO_BUTTON_H
#define GUI_RADIO_BUTTON_H

#include "GUI/GUIItem.hpp"

class CheckBox;

class RadioButtons : public GUIItem {
    public:
        RadioButtons(int nbButtons, sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(100, 100), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~RadioButtons();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        void setShapeColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0);
        void setShapeOutlineThickness(float thickness);

        int getSelected();
        void setSelected(int id);
        void setOrientation(int isVertical, float padding = 0.f);
        int isVertical();
        float getPadding();

        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        sf::Vector2f getPosition();

        int getButtonCount();
        void setButtonCount(int newCount);

        void setShapeFillColoredUpdate(sf::Color *colors, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0);

    protected:
        void setDataRec() {};
        void addButton(int i);
        void updateShapeStateFull(void);
        void updateShapeState(void);

        int m_isVertical;
        float m_padding;
        int m_selected;
        int m_nbButtons;
        int m_allocatedSize;
        CheckBox **m_buttons;
};

#endif /* !GUI_RADIO_BUTTON_H */