/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** TextItem
*/

#ifndef GUI_TEXTITEM_H
#define GUI_TEXTITEM_H

#include "GUI/GUIAbstractText.hpp"

class TextItem : public GUIAbstractText
{
    public:
        TextItem() {};
        virtual ~TextItem() {};

        std::string getString(void);
        void setString(std::string str);
        void setTextColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0);
        void setTextOutlineThickness(float thickness);
        void setTextParams(sf::Font *font, unsigned int charSize = 0);
        void setFont(sf::Font *font);
        void setCharacterSize(unsigned int charSize);

        void clearTextUpdateType(void);

        void setTextFillColoredUpdate(sf::Color *colors);
        void setTextFillColoredUpdate(sf::Color normal, sf::Color clicked);
        void setTextFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked);

        void setTextOutColoredUpdate(sf::Color *colors);
        void setTextOutColoredUpdate(sf::Color normal, sf::Color clicked);
        void setTextOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked);

        void setPosition(sf::Vector2f pos) {m_text.setPosition(pos);};
        void setPosition(float x, float y) {m_text.setPosition(x, y);};
        sf::Vector2f getPosition() {return m_text.getPosition();};

        void setTag(int tag) {m_tag = tag;};
        int getTag() {return m_tag;};
        void setData(GameDataRef data) {m_data = data;setDataRec();};
        GameDataRef getData(void) {return m_data;};
    
    protected:
        void initText(int nbStates, std::string str, sf::Font *font = nullptr, unsigned int charSize = 15);
        void updateTextStateFull(void);
        void updateTextState(void);

};

#endif /* !GUI_TEXTITEM_H */
