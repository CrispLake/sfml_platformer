#include "Button.h"
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "MathUtils.h"
#include "Constants.h"
#include "Game.h"

Button::Button(Game* pGame, float radius, sf::Vector2f position) : m_radius(radius), m_pGame(pGame)
{
    float rOffset = CoinRadius;
    position -= sf::Vector2f(rOffset, rOffset);
    position += sf::Vector2f(TileSizeX, TileSizeY) * 0.5f;
    sf::Transformable::setPosition(position);
    m_color = sf::Color::Red;
}

bool Button::collidesWith(Rectangle* other)
{
    sf::Vector2f otherPosition = other->getPosition();
    sf::Vector2f otherSize = other->getSize();

    float otherLeft = otherPosition.x;
    float otherRight = otherPosition.x + otherSize.x;
    float otherTop = otherPosition.y;
    float otherBottom = otherPosition.y + otherSize.y;
 
    if (getCenter().x - m_radius * 0.5f < otherRight &&
        getCenter().x + m_radius > otherLeft &&
        getCenter().y - m_radius * 0.5f < otherBottom &&
        getCenter().y + m_radius > otherTop) {
        return true;
    }
    return false;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape graphicsCircle(m_radius);

    graphicsCircle.setFillColor(m_color);
    graphicsCircle.setPosition(getPosition());
    target.draw(graphicsCircle);
}

sf::Vector2f Button::getCenter()
{
    float rOffset = m_radius * 0.5f;

    return getPosition() + sf::Vector2f(rOffset, rOffset);
}

void Button::setActivated()
{
    if (!m_isActivated)
    {
        m_color = sf::Color::Green;
        m_pGame->DecreaseButtonCounter();
        m_isActivated = true;
    }
}