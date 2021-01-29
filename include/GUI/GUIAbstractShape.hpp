/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIAbstractShape
*/

#ifndef GUI_ABSTRACT_SHAPE_H
#define GUI_ABSTRACT_SHAPE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "GUI/GUIAbstract.hpp"

class GUIAbstractShape : public GUIAbstract
{
    public:
        GUIAbstractShape() {};
        virtual ~GUIAbstractShape() {};

        virtual void setShapeColors(sf::Color fill, sf::Color outline = sf::Color::Transparent, float outlineThickness = 0, int shape = 0) = 0;
        virtual void setShapeOutlineThickness(float thickness, int shape = 0) = 0;

        virtual void clearShapeUpdateTypes(int shape = -1) = 0;

        virtual void setShapeFillColoredUpdate(sf::Color *colors, int shape = 0) = 0;
        virtual void setShapeFillColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0) = 0;
        virtual void setShapeFillColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0) = 0;

        virtual void setShapeOutColoredUpdate(sf::Color *colors, int shape = 0) = 0;
        virtual void setShapeOutColoredUpdate(sf::Color normal, sf::Color clicked, int shape = 0) = 0;
        virtual void setShapeOutColoredUpdate(sf::Color normal, sf::Color hover, sf::Color clicked, int shape = 0) = 0;

        virtual void setShapeTexturedUpdate(sf::Texture **textures, int shape = 0) = 0;
        virtual void setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &clicked, int shape = 0) = 0;
        virtual void setShapeTexturedUpdate(sf::Texture &normal, sf::Texture &hover, sf::Texture &clicked, int shape = 0) = 0;

        virtual void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect *rects, int shape = 0) = 0;
        virtual void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect clicked, int shape = 0) = 0;
        virtual void setShapeTexturedRectUpdate(sf::Texture *texture, sf::IntRect normal, sf::IntRect hover, sf::IntRect clicked, int shape = 0) = 0;
        virtual void setShapeTexturedRectUpdate(sf::Texture *texture, sf::Vector2i start, sf::Vector2i size, int isVertical, int shape = 0) = 0;
    
    protected:
        virtual void clearShapeUpdateType(int shape) = 0;
        virtual void setDataRec() = 0;
        virtual void initShape(int nbStates) = 0;
        virtual void updateShapeStateFull(void) = 0;
        virtual void updateShapeState(void) = 0;

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

#endif /* !GUI_ABSTRACT_SHAPE_H */