#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Rectangle;

class Ball : public sf::Drawable, public sf::Transformable
{
public:
    Ball(float radius, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Ball() {}
    
    bool collidesWith(Rectangle* other);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getCenter();

    void updatePhysics(float deltaTime);
    
    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }

private:

    float   m_radius;
    float   m_lifeTimer = 3.0f;
    bool    m_isDead = false;
    
};