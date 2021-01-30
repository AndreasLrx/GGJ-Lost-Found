/*
** EPITECH PROJECT, 2021
** GGJ Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Room;

class Entity : public sf::Drawable
{
    public:
        virtual ~Entity() {};

        virtual void init(sf::Texture const& texture, sf::Vector2f pos = { 0, 0 }, sf::Vector2f scale = { 0, 0 }) = 0;
        virtual void handleInput(sf::Event event) = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

        sf::Vector2f getPosition() const;
        sf::Vector2f getScale();
        float getOrientation();

        /// Override this to handle sprite updates
        virtual void onPositionChanged() {};
        virtual void onScaleChanged() {};
        virtual void onOrientationChanged() {};

        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        bool move(sf::Vector2f offset);
        bool move(float ox, float oy);

        void setScale(sf::Vector2f scale);
        void setScale(float sx, float sy);
        
        void setOrientation(float orientation);

        bool isAlive();

    protected:
        bool m_isAlive;
        Room *m_room;

    private:
        sf::Vector2f m_pos;
        sf::Vector2f m_scale;
        float m_orientation = 0;
};

inline sf::Vector2f Entity::getPosition() const
{
    return this->m_pos;
}

inline sf::Vector2f Entity::getScale()
{
    return this->m_scale;
}

inline float Entity::getOrientation()
{
    return this->m_orientation;
}

inline void Entity::setPosition(sf::Vector2f pos)
{
    if (pos == this->m_pos)
        return;
    this->m_pos = pos;
    this->onPositionChanged();
}

inline void Entity::setPosition(float x, float y)
{
    this->setPosition({ x, y });
}

inline bool Entity::move(sf::Vector2f offset)
{
    if (offset == sf::Vector2f(0, 0))
        return false;
    this->setPosition(this->m_pos + offset);
    return true;
}

inline bool Entity::move(float ox, float oy)
{
    return this->move({ ox, oy });
}

inline void Entity::setScale(sf::Vector2f scale)
{
    if (scale == this->m_scale)
        return;
    this->m_scale = scale;
    this->onScaleChanged();
}

inline void Entity::setScale(float sx, float sy)
{
    this->setScale({ sx, sy });
}

inline void Entity::setOrientation(float orientation)
{
    if (orientation == this->m_orientation)
        return;
    this->m_orientation = orientation;
    this->onOrientationChanged();
}

inline bool Entity::isAlive()
{
    return this->m_isAlive;
}

#endif /* !ENTITY_HPP */
