/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIManager
*/

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <vector>
#include <queue>
#include "GameEngine/Core.hpp"
#include "GUI/GUIAbstract.hpp"

class GUIManager
{
    public:
        GUIManager() {};
        GUIManager(GameDataRef data);
        ~GUIManager() {};

        void setData(GameDataRef data);

        void handleInput(sf::Event &event);
        void update(float dt);
        void draw(float interpolation);

        void addItem(GUIAbstract *item, int tag);
        GUIAbstract *getItem(int tag);

    private:
        GameDataRef m_data;
        std::map<int, GUIAbstract *> m_items;
};

#endif /* !GUI_MANAGER_H */