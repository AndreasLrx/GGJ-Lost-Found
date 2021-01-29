/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextButton
*/

#ifndef GUI_TEXT_BUTTON_H
#define GUI_TEXT_BUTTON_H

#include <string>
#include "GUI/TextItem.hpp"
#include "GUI/Button.hpp"

class TextButton : public Button, public TextItem
{
    public:
        TextButton(std::string str = "", sf::Font *font = nullptr, sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(100, 100), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~TextButton();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        void setString(std::string str);

        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        sf::Vector2f getPosition();

        void setTag(int tag) {Button::m_tag = tag;};
        int getTag() {return Button::m_tag;};
        void setData(GameDataRef data) {Button::m_data = data;setDataRec();};

        GUIAbstract *getBase() {return static_cast<Button *>(this);};

    private:
        void setDataRec() {};
        void replaceText();

};

#endif /* !GUI_TEXT_BUTTON_H */