#include "Ball.h"
#include <SFML/Graphics.hpp>
#include "Rectangle.h"
#include "MathUtils.h"
#include "Constants.h"
#include "Game.h"

Ball::Ball(Game* pGame, float radius, sf::Vector2f position)  :
    m_radius(radius),
    m_lifeTimer(BallLifetime),
    m_isDead(false),
    m_CurrentXSpeed(0.0f),
    m_CurrentYSpeed(Gravity / 2),
    m_pGame(pGame)
{
    float rOffset = BallRadius;
    position -= sf::Vector2f(rOffset, rOffset);
    position += sf::Vector2f(TileSizeX, TileSizeY) * 0.5f;
    sf::Transformable::setPosition(position);
}

bool Ball::collidesWith(Rectangle* other)
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

void Ball::updateXSpeed(float deltaTime)
{
    sf::Transformable::move(m_CurrentXSpeed * deltaTime, 0.0f);
    auto pRectangles = m_pGame->getRectangles();
    for (auto& pRectangle : pRectangles)
    {
        if (collidesWith(pRectangle))
        {
            m_CurrentXSpeed = -m_CurrentXSpeed;
            sf::Transformable::move(sf::Vector2f(m_CurrentXSpeed * deltaTime, 0.0f));
        }
    }
}

void Ball::updateYSpeed(float deltaTime)
{
    sf::Transformable::move(0.0f, m_CurrentYSpeed * deltaTime);
    auto pRectangles = m_pGame->getRectangles();
    for (auto& pRectangle : pRectangles)
    {
        if (collidesWith(pRectangle))
        {
            m_CurrentYSpeed = -m_CurrentYSpeed;
            sf::Transformable::move(0.0f, m_CurrentYSpeed * deltaTime);
        }
    }
}

void Ball::updatePhysics(float deltaTime)
{
    float yPos = getPosition().y;
    
    m_isDead = yPos > ScreenHeight;
    m_lifeTimer -= deltaTime;
    if (m_lifeTimer < 0.0f)
        m_isDead = true;
    updateXSpeed(deltaTime);
    updateYSpeed(deltaTime);
}
