/*
** EPITECH PROJECT, 2021
** GGJ States
** File description:
** LevelSelect
*/

#include "States/LevelSelectState.hpp"
#include "States/GameState.hpp"
#include "GUI/TextButton.hpp"

LevelSelectState::LevelSelectState(GameDataRef data)
{
    m_data = data;
    m_gui = new GUIManager(data);

    initBtn("Tutorial", sf::Vector2f(525 * SCL(this), 120 * SCL(this)), 0, [](GUIAbstract *btn, int tag){
        if (tag == 0)
            btn->getData()->machine.addState(StateRef(new GameState(btn->getData())), 1);
        btn->getData()->assets.stopMusic("menu_music");});
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            initBtn("Level " + std::to_string(x + y * 3 + 1), sf::Vector2f((160 + (x * 365)) * SCL(this), (300 + y * 100) * SCL(this)), x * 3 + y + 1);
        }
    }
}

LevelSelectState::~LevelSelectState()
{
    delete m_gui;
}

void LevelSelectState::initBtn(std::string text, sf::Vector2f pos, int tag, inputReactFct input)
{
    TextButton *btn = new TextButton(text, m_data->assets.getFont("spincycle"), pos, sf::Vector2f(230  * SCL(this), 69.3f  * SCL(this)), input);
    btn->setShapeTexturedRectUpdate(m_data->assets.getTexture("button"), {0, 0, 165, 52}, {0, 0, 165, 52}, {0, 52, 165, 52});
    btn->setCharacterSize(30  * SCL(this));
    btn->setTextFillColoredUpdate(sf::Color(205, 240, 238), sf::Color(247, 239, 201), sf::Color(247, 239, 201));

    m_gui->addItem(btn->getBase(), tag);
}

void LevelSelectState::handleInput()
{
    sf::Event event;

    while (m_data->wind.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_data->wind.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            m_data->machine.removeState();
        m_gui->handleInput(event);
    }
}

void LevelSelectState::update(float dt)
{
    m_gui->update(dt);
}

void LevelSelectState::draw(sf::RenderTarget& target, float interpolation)
{
    target.clear(sf::Color(130, 130, 130));
    m_gui->draw(interpolation);
}