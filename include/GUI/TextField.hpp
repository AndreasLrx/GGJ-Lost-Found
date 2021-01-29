/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextField
*/

#ifndef GUI_TEXTFIELD_H
#define GUI_TEXTFIELD_H

#include <string>
#include "GUI/TextShape.hpp"

class CheckBox;

class TextField : public TextShape
{
    public:
        TextField(sf::Font *font, std::string text, sf::Vector2f pos = sf::Vector2f(100, 100), sf::Vector2f size = sf::Vector2f(100, 100), \
        inputReactFct input = NULL, updateReactFct update = NULL);
        ~TextField();

        void handleInput(sf::Event event);
        void update(float dt);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

        std::string getString(void);
        void setString(std::string str);
        std::string getWhitelist(void);
        void setWhitelist(std::string whitelist);
        int isSelected();
        void setSelected(int selected);

        GUIAbstract *getBase() {return static_cast<GUIAbstract *>(static_cast<GUIItem *>(this));};

        void setShapeColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0);
        void setShapeOutlineThickness(float thickness);
        
        void setShapeFillColoredUpdate(sf::Color *colors, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0);

    protected:
        void handleText(sf::Uint32 unicode);
        void moveCursor(sf::Keyboard::Key key);
        void setDataRec();
        void updateStateFull(void);
        void updateState(void);

        int m_cursor;
        float m_cursorClock;
        std::string m_whitelist;
        std::string m_blacklist;
        std::string m_str;
        CheckBox *m_rect;
};

#endif /* !GUI_TEXTFIELD_H */