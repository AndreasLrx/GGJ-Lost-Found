/*
** EPITECH PROJECT, 2021
** GGJ Animated Sprite
** File description:
** Animated Sprites
*/

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>


class AnimatedSprite: public sf::Drawable, public sf::Transformable
{
public:
    using AnimationEndListener = std::function<void(AnimatedSprite&)>;

    AnimatedSprite();
    AnimatedSprite(const sf::Texture& texture, std::size_t frameCount, sf::IntRect const frames[], float speed = 1.0f);

    /// Updates the animation frames
    void update(float dt);

    void setTexture(const sf::Texture& texture, bool resetFrames = false);
    void setTextureFrames(std::size_t frame_count, sf::IntRect const frames[]);
    void setAnimationSpeed(float speed);
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    void setAnimationEndListener(AnimationEndListener listener);
    void setMirrored(bool mirrored);
    bool isMirrored();
    void resetFrame();
    void randomFrame();
    void setProgress(float frame);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_inner;
    std::vector<sf::IntRect> m_frames;
    float m_speed = 1.0f;
    float m_frame = 0.0f;
    float m_frameMax = 0.0f;
    bool m_isMirrored = false;
    AnimationEndListener m_listener;
};

inline void AnimatedSprite::setAnimationEndListener(AnimationEndListener listener)
{
    this->m_listener = listener;
}

inline void AnimatedSprite::setMirrored(bool mirrored)
{
    this->m_isMirrored = mirrored;
}

inline bool AnimatedSprite::isMirrored()
{
    return this->m_isMirrored;
}

inline void AnimatedSprite::setProgress(float frame)
{
    this->m_frame = this->m_frameMax * frame;
}

#endif // !defined(SPRITE_HPP)