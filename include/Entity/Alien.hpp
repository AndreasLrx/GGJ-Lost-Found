/*
** EPITECH PROJECT, 2021
** GGJ Alien Player
** File description:
** alien player class
*/

#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <vector>
#include "Entity/Entity.hpp"

class Tentacle;

class Alien : public Entity
{
public:
    Alien(GameDataRef gameData);
	~Alien();

    void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 }) override;
    void handleInput(sf::Event event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void onPositionChanged() override;
    void onScaleChanged() override;
    void onOrientationChanged() override;

private:
    sf::Sprite m_slimeSprite;
    sf::Sprite m_bodySprite;
    sf::Sprite m_eyeSprite;
    sf::IntRect m_bodyRect;
    sf::IntRect m_slimeRect;
    sf::IntRect m_eyeRect;
    GameDataRef m_gameData;
    std::vector<Tentacle *> m_passiveTentacles;
    Tentacle *m_active_tentacle;

    void initTentacle(Tentacle* tentacle, std::size_t index, sf::Texture const& texture, sf::Vector2f pos, sf::Vector2f scale);
    void spreadTentacles();
};

#endif // !defined(ALIEN_HPP)