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
    loadTexture("button", "res/Textures/GUI/Button.png");
    loadTexture("menu", "res/Textures/Menu.png");
    loadTexture("scientist", "res/Textures/scientist.png");
    loadTexture("soldier", "res/Textures/soldier.png");
    loadTexture("berserk", "res/Textures/berserk.png");
    loadTexture("squares", "res/Textures/squares.png");
    loadTexture("alien", "res/Textures/alien.png");
    loadFont("spincycle", "res/Fonts/spincycle_ot.otf");
    loadTexture("TestTile_Set", "res/Textures/tile.png");
    loadTexture("bg", "res/Textures/bg.png");
    loadTexture("laser", "res/Textures/laser.png");
}

void AssetManager::loadTexture(std::string name, std::string fileName)
{
    sf::Texture *texture = new sf::Texture;

    if (texture->loadFromFile(fileName)) {
        texture->setSmooth(true);
        m_textures[name] = texture;
    }
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
