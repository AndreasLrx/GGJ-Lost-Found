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
    loadMusic("menu_music", "res/Musics/main_menu_1.ogg");
    loadMusic("battletheme", "res/Musics/battletheme-rock.ogg");
    loadSound("piou1", "res/Sounds/laser_type1.ogg");
    loadSound("piou2", "res/Sounds/laser_type2.ogg");
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
    } else
        delete texture;
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
    else
        delete font;
}

sf::Font *AssetManager::getFont(std::string name)
{
    return m_fonts.at(name);
}

void AssetManager::loadSound(std::string name, std::string fileName)
{
    sf::SoundBuffer *sound = new sf::SoundBuffer;

    if (sound->loadFromFile(fileName))
        m_sounds[name] = sound;
    else
        delete sound;
}

sf::SoundBuffer *AssetManager::getSound(std::string name)
{
    return m_sounds[name];
}

void AssetManager::loadMusic(std::string name, std::string fileName)
{
    sf::Music *music = new sf::Music;

    if (music->openFromFile(fileName))
        m_musics[name] = music;
    else
        delete music;
}

sf::Music *AssetManager::getMusic(std::string name)
{
    return m_musics[name];
}

void AssetManager::playSound(std::string name)
{
    sf::SoundBuffer *buffer = getSound(name);
    if (!buffer)
        return;
    sf::Sound *sound = new sf::Sound();

    sound->setBuffer(*buffer);
    sound->play();
    m_soundsPlaying.push_back(sound);
}

void AssetManager::playMusic(std::string name)
{
    sf::Music *music = getMusic(name);

    if (!music)
        return;
    music->play();
    m_musicsPlaying.push_back(music);
}

void AssetManager::updateSounds()
{
    for (size_t i = 0; i < m_soundsPlaying.size(); i++) {
        if (m_soundsPlaying[i]->getStatus() == sf::Sound::Stopped) {
            delete m_soundsPlaying[i];
            m_soundsPlaying.erase(m_soundsPlaying.begin() + i);
            i--;
        }
    }
}

void AssetManager::keepSound(sf::Sound *sound)
{
    m_soundsPlaying.push_back(sound);
}

void AssetManager::stopMusic(std::string name)
{
    sf::Music *music = getMusic(name);

    if (!music)
        return;
    m_musicsPlaying.erase(std::remove(m_musicsPlaying.begin(), m_musicsPlaying.end(), music), m_musicsPlaying.end());
    music->stop();
}

void AssetManager::stopMusics()
{
    for (size_t i = 0; i < m_musicsPlaying.size(); i++)
        m_musicsPlaying[i]->stop();
    m_musicsPlaying.clear();
}

void AssetManager::stopSounds()
{
    for (size_t i = 0; i < m_musicsPlaying.size(); i++) {
        m_soundsPlaying[i]->stop();
        delete m_soundsPlaying[i];
    }
    m_soundsPlaying.clear();
}