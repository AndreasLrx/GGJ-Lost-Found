/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIItem
*/

#ifndef GUI_ITEM_HPP
#define GUI_ITEM_HPP

#include <SFML/Graphics.hpp>
#include "GUI/GUIAbstractShape.hpp"

class GUIItem : public GUIAbstractShape
{
    public:
        GUIItem() {};
        virtual ~GUIItem() {};

        void addShape(sf::Shape *shape);

        void setShapeColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0, int shape = 0);
        void setShapeOutlineThickness(float thickness, int shape = 0);

        void clearShapeUpdateTypes(int shape = -1);

        void setShapeFillColoredUpdate(sf::Color *colors, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0);
        void setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0);

        void setShapeOutColoredUpdate(sf::Color *colors, int shape = 0);
        void setShapeOutColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0);
        void setShapeOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0);

        void setShapeTexturedUpdate(sf::Texture **textures, int shape = 0);
        void setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &clicked, int shape = 0);
        void setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &hover, sf::Texture &clicked, int shape = 0);

        void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect *rects, int shape = 0);
        void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect clicked, int shape = 0);
        void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect hover, sf::IntRect clicked, int shape = 0);
        void setShapeTexturedRectUpdate(sf::Texture *texture, sf::Vector2i start, sf::Vector2i size, int isVertical, int shape = 0);

        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        sf::Vector2f getPosition();

        void setTag(int tag) {m_tag = tag;};
        int getTag() {return m_tag;};
        void setData(GameDataRef data) {m_data = data;setDataRec();};
        GameDataRef getData(void) {return m_data;};
        int getState(void) {return m_state;};
    
    protected:
        void clearShapeUpdateType(int shape);
        virtual void setDataRec() = 0;
        void initShape(int nbStates);
        void updateShapeStateFull(void);
        void updateShapeState(void);

        int m_tag;
        int m_nbStates;
        int m_state;
        GameDataRef m_data;
        inputReactFct m_inputReact;
        updateReactFct m_updateReact;

        std::vector<sf::Shape *> m_shapes;
        std::vector<uint32_t> m_updateTypes;
        std::vector<sf::Color *> m_fillColors;
        std::vector<sf::Color *> m_outColors;
        std::vector<sf::Texture **> m_textures;
        std::vector<sf::IntRect *> m_textureRects;
};

#endif /* !GUI_ITEM_HPP */