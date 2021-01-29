/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** CheckBox
*/

#ifndef GUI_CHECKBOX_H
#define GUI_CHECKBOX_H

#include "GUI/Button.hpp"
#include "GUI/RadioButtons.hpp"
#include "GUI/TextField.hpp"

class CheckBox : public Button {
    friend RadioButtons;
    friend TextField;
    public:
        CheckBox(sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(100, 100), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~CheckBox();

        void handleInput(sf::Event event);

        void setSelected(bool isSelected);
        bool isSelected(void);
    
    private:
        void setDataRec() {};
};

#endif /* !GUI_CHECKBOX_H */