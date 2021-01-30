/*
** EPITECH PROJECT, 2021
** GGJ GUI
** File description:
** GUIManager
*/

#include "GUI/GUIManager.hpp"

GUIManager::GUIManager(GameDataRef data)
{
    setData(data);
}

void GUIManager::setData(GameDataRef data)
{
    m_data = data;
}

void GUIManager::handleInput(sf::Event &event)
{
    std::map<int, GUIAbstract *>::iterator it;

    for (it = m_items.begin(); it != m_items.end(); it++)
        it->second->handleInput(event);
}

void GUIManager::update(float dt)
{
    std::map<int, GUIAbstract *>::iterator it;

    for (it = m_items.begin(); it != m_items.end(); it++)
        it->second->update(dt);
}

void GUIManager::draw(float interpolation)
{
    std::map<int, GUIAbstract *>::iterator it;

    for (it = m_items.begin(); it != m_items.end(); it++)
        m_data->wind.draw(*it->second);
    if (interpolation)
        return;
}

void GUIManager::addItem(GUIAbstract *item, int tag)
{
    item->setTag(tag);
    item->setData(m_data);
    m_items[tag] = item;
}

GUIAbstract *GUIManager::getItem(int tag)
{
    return m_items.at(tag);
}