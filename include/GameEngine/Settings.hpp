/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** Settings
*/

#ifndef GAME_ENGINE_SETTINGS_HPP
#define GAME_ENGINE_SETTINGS_HPP

#include <SFML/Graphics.hpp>

#define SCL(state) (state->getData()->settings.getScale())

class Settings {
    public:
        Settings() {};
        ~Settings() {};

        void setWindSize(sf::Vector2u size);
        void setWindSize(unsigned int x, unsigned int y);
        float getScale() {return m_scale;};

    private:
        sf::Vector2u m_windSize;
        unsigned int m_framerate;
        float m_scale;
};

#endif /* !GAME_ENGINE_SETTINGS_HPP */