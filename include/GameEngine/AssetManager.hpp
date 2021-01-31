/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** AssetManagers
*/

#ifndef GE_ASSET_MANAGER_H
#define GE_ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class AssetManager
{
    public:
        AssetManager() {};
        ~AssetManager();

        void loadAll(void);

        void loadTexture(std::string name, std::string fileName);
        sf::Texture *getTexture(std::string name);

        void loadFont(std::string name, std::string fileName);
        sf::Font *getFont(std::string name);

        void loadSound(std::string name, std::string fileName);
        sf::SoundBuffer *getSound(std::string name);

        void loadMusic(std::string name, std::string fileName);
        sf::Music *getMusic(std::string name);

        void updateSounds();
        void keepSound(sf::Sound *sound);

        void playSound(std::string name);
        void playMusic(std::string name, bool loop = true);
        void stopMusic(std::string name);
        void stopMusics();
        void stopSounds();

    private:
        std::map<std::string, sf::Texture *> m_textures;
        std::map<std::string, sf::Font *> m_fonts;
        std::map<std::string, sf::SoundBuffer *> m_sounds;
        std::map<std::string, sf::Music *> m_musics;

        std::vector<sf::Music *> m_musicsPlaying;
        std::vector<sf::Sound *> m_soundsPlaying;
};

#endif /* !GE_ASSET_MANAGER_H */