/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIAbstract
*/

#ifndef GUI_ABSTRACT_CLASS
#define GUI_ABSTRACT_CLASS

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "GameEngine/Core.hpp"

enum GUI_STATES {NORMAL = 0, HOVER = 1, CHECKED = 1, CLICKED = 2};
enum GUI_UPDATE_TYPES {COLOR = 1, OUT_COLORED = 2, TEXTURED = 4, TEXTURED_RECT = 8};

class GUIAbstract;

using inputReactFct = std::function<void(GUIAbstract *, int)>;
using updateReactFct = std::function<void(GUIAbstract *, int)>;

class GUIAbstract : public sf::Drawable
{
    public:
        GUIAbstract() {};
        virtual ~GUIAbstract() {};
        virtual void handleInput(sf::Event event) = 0;
        virtual void update(float dt) = 0;

        virtual void setPosition(sf::Vector2f pos) = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual sf::Vector2f getPosition() = 0;

        virtual void setTag(int tag)  = 0;
        virtual int getTag() = 0;
        virtual void setData(GameDataRef data) = 0;
    
    protected:
        virtual void setDataRec() = 0;

        int m_tag;
        int m_nbStates;
        int m_state;
        GameDataRef m_data;
        inputReactFct m_inputReact;
        updateReactFct m_updateReact;
};

#endif /* !GUI_ABSTRACT_CLASS */