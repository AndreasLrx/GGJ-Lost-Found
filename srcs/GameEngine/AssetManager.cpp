/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** AssetManager
*/

#include <iostream>
#include "GameEngine/AssetManager.hpp"

AssetManager::~AssetManager()
{
    std::map<std::string, sf::Texture *>::iterator it_texture;
    std::map<std::string, sf::Font *>::iterator it_fonts;

    for (it_texture = m_textures.begin(); it_texture != m_textures.end(); it_texture++)
        delete it_texture->second;
    for (it_fonts = m_fonts.begin(); it_fonts != m_fonts.end(); it_fonts++)
        delete it_fonts->second;
}

void AssetManager::loadAll(void)
{
    loadTexture("iceButtons", "res/Textures/GUI/buttons.png");
    loadFont("roboto", "res/Fonts/roboto_regular.ttf");
    loadTexture("TestTile_Set", "res/Textures/tileset_test.png");
}

void AssetManager::loadTexture(std::string name, std::string fileName)
{
    sf::Texture *texture = new sf::Texture;

    if (texture->loadFromFile(fileName))
        m_textures[name] = texture;
}

sf::Texture *AssetManager::getTexture(std::string name)
{
    return m_textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string fileName)
{
    sf::Font *font = new sf::Font;

    if (font->loadFromFile(fileName))
        m_fonts[name] = font;
}

sf::Font *AssetManager::getFont(std::string name)
{
    return m_fonts.at(name);
}
