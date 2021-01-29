/*
** EPITECH PROJECT, 2021
** GGJ GameEngine
** File description:
** AssetManagers
*/

#ifndef GE_ASSET_MANAGER_H
#define GE_ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
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

    private:
        std::map<std::string, sf::Texture *> m_textures;
        std::map<std::string, sf::Font *> m_fonts;
};

#endif /* !GE_ASSET_MANAGER_H */