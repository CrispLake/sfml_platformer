#include "Ball.h"
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "MathUtils.h"
#include "Constants.h"

Ball::Ball(float radius, sf::Vector2f position) : m_radius(radius)
{
    float rOffset = BallRadius;
    position -= sf::Vector2f(rOffset, rOffset);
    position += sf::Vector2f(TileSizeX, TileSizeY) * 0.5f;
    sf::Transformable::setPosition(position);
}

bool Ball::collidesWith(Rectangle* other)
{
    sf::Vector2f position = other->getPosition();
    sf::Vector2f size = other->getSize();

    sf::Vector2f topLeft = position;
    sf::Vector2f topRight = position + sf::Vector2f(size.x, 0);
    sf::Vector2f botLeft = position + sf::Vector2f(0, size.y);
    sf::Vector2f botRight = position + size;

    return VecLength(topRight - getCenter()) < m_radius ||
        VecLength(topLeft - getCenter()) < m_radius ||
        VecLength(botRight - getCenter()) < m_radius ||
        VecLength(botLeft - getCenter()) < m_radius;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape graphicsCircle(m_radius);

    graphicsCircle.setFillColor(sf::Color::Red);
    graphicsCircle.setPosition(getPosition());
    target.draw(graphicsCircle);
}

sf::Vector2f Ball::getCenter()
{
    float rOffset = m_radius * 0.5f;

    return getPosition() + sf::Vector2f(rOffset, rOffset);
}

void Ball::updatePhysics(float deltaTime)
{
    float yPos = getPosition().y;
    
    m_isDead = yPos > ScreenHeight;
}
