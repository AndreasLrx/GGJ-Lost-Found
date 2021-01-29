/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** ClickableText
*/

#ifndef GUI_CLICKABLE_TEXT_H
#define GUI_CLICKABLE_TEXT_H

#include "GUI/TextButton.hpp"

class ClickableText : public TextItem
{
    public:
        ClickableText(std::string str = "", sf::Font *font = nullptr, sf::Vector2f pos = sf::Vector2f(100, 100), \
        unsigned int charSize = 15, inputReactFct input = NULL, updateReactFct update = NULL);
        ~ClickableText();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        int isClicked(void);

        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        sf::Vector2f getPosition();

        void setTag(int tag) {m_tag = tag;};
        int getTag() {return m_tag;};
        void setData(GameDataRef data) {m_data = data;};

    private:
        void setDataRec() {};
};

#endif /* !GUI_CLICKABLE_TEXT_H */