/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIAbstractText
*/

#ifndef GUI_ABSTRACT_TEXT_H
#define GUI_ABSTRACT_TEXT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "GUI/GUIAbstract.hpp"

enum GUI_UPDATE_TYPES_TEXT {TEXT_COLORED = 1, TEXT_OUT_COLORED = 2};

class GUIAbstractText : public GUIAbstract
{
    public:
        GUIAbstractText() {};
        virtual ~GUIAbstractText() {};

        virtual std::string getString(void) = 0;
        virtual void setString(std::string str) = 0;
        virtual void setTextColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0) = 0;
        virtual void setTextOutlineThickness(float thickness) = 0;
        virtual void setTextParams(sf::Font *font, unsigned int charSize = 0) = 0;
        virtual void setFont(sf::Font *font) = 0;
        virtual void setCharacterSize(unsigned int charSize) = 0;

        virtual void clearTextUpdateType(void) = 0;

        virtual void setTextFillColoredUpdate(sf::Color *colors) = 0;
        virtual void setTextFillColoredUpdate(sf::Color normal, sf::Color clicked) = 0;
        virtual void setTextFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked) = 0;

        virtual void setTextOutColoredUpdate(sf::Color *colors) = 0;
        virtual void setTextOutColoredUpdate(sf::Color normal, sf::Color clicked) = 0;
        virtual void setTextOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked) = 0;
    
    protected:
        virtual void initText(int nbStates, std::string str, sf::Font *font = nullptr, unsigned int charSize = 15) = 0;
        virtual void updateTextStateFull(void) = 0;
        virtual void updateTextState(void) = 0;

        unsigned int m_textUpdateTypes;
        unsigned int m_charSize;
        sf::Font *m_font;
        sf::Text m_text;
        sf::Color *m_textFillColors;
        sf::Color *m_textOutColors;
};

#endif /* !GUI_ABSTRACT_TEXT_H */