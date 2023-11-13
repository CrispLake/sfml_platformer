#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>

class Rectangle;
class Game;

class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(Game* pGame, float radius, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Button() {}
    
    bool collidesWith(Rectangle* other);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getCenter();
    float        getRadius() { return m_radius; }

    void setActivated();

private:

    float       m_radius;
    sf::Color   m_color;

    bool        m_isActivated = false;

    Game*   m_pGame;
};
