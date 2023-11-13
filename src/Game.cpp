#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "InputHandler.h"
#include "Player.h"
#include "resources/Resources.h"
#include "Rectangle.h"
#include "Coin.h"
#include "Door.h"
#include "Ball.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
    m_pDoor(std::make_unique<Door>(this)),
    m_score(0),
    m_clearedLevels(0),
    m_ballCount(BallMaxCount),
    m_ballReloadTime(0),
    m_ballThrowDelay(BallThrowDelay)
{
    
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{
    
}

bool Game::initialise(sf::Vector2f pitchSize)
{
    m_pClock->restart();
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }

    //Initialize shapes from TileMap
    resetLevel(MapArray1);
    return true;
}

void Game::resetLevel(const int* tileMap)
{
    m_pCoins.clear();
    m_pRectangles.clear();

    m_pPlayer->setIsDead(false);
    m_pDoor->setTriggered(false);

    const sf::Vector2f tileSize(TileSizeX, TileSizeY);

    for (int y = 0; y < GridSize; y++)
    {
        for (int x = 0; x < GridSize; x++)
        {
            int i = x + y * GridSize;

            const sf::Vector2f worldPos = sf::Vector2f(x * tileSize.x, y * tileSize.y);
            switch (tileMap[i])
            {
                case    eTile::eCoin:
                    m_pCoins.push_back(std::make_unique<Coin>(CoinRadius, worldPos));
                    break;
                case    eTile::eBlock:
                    m_pRectangles.push_back(std::make_unique<Rectangle>(tileSize, worldPos));
                    break;
                case    eTile::ePlayerSpawn:
                    m_pPlayer->setPosition(worldPos);
                    break;
                case    eTile::eDoor:
                    m_pDoor->setPosition(worldPos);
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->updatePhysics(deltaTime);
            m_pPlayer->update(deltaTime);

            updateBallDelays(deltaTime);
            updateBallPhysics(deltaTime);
            

            if (m_pPlayer->isDead())
            {
                m_pPlayer->clearCoins();
                m_clearedLevels = 0;
                resetLevel(MapArray1);
            }
                
            if (m_pDoor->isTriggered())
            {
                m_clearedLevels++;
                if (m_clearedLevels == LevelCount)
                {
                    m_pPlayer->clearCoins();
                    m_clearedLevels = 0;
                    m_score = 0;
                    m_state = State::WAITING;
                    m_pClock->restart();
                    resetLevel(MapArray1);
                }
                else
                {
                    resetLevel(MapArray2);
                }
                
            }
        }
        break;
    }
    int i = 0;
    while (i < m_pCoins.size())
    {
        if (m_pCoins[i]->getCollected())
        {
            std::swap(m_pCoins[i], m_pCoins.back());
            m_pCoins.pop_back();
            continue;
        }
        i++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
    else
    {
        sf::Text coinText;
        coinText.setFont(m_font);
        coinText.setFillColor(sf::Color::White);
        coinText.setStyle(sf::Text::Bold);
        coinText.setString(std::to_string(m_pPlayer->getCoins()));
        coinText.setColor(sf::Color::Yellow);
        coinText.setPosition(sf::Vector2f(ScreenWidth - coinText.getLocalBounds().getSize().x - 5, 0));
        target.draw(coinText);
    }
    sf::Text ballText;
    ballText.setFont(m_font);
    ballText.setFillColor(sf::Color::White);
    ballText.setStyle(sf::Text::Bold);
    ballText.setString("Balls: " + std::to_string(m_ballCount));
    ballText.setColor(sf::Color::Yellow);
    ballText.setPosition(sf::Vector2f(5, 0));
    target.draw(ballText);

    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pCoins)
    {
        temp->draw(target, states);
    }
    for (auto& temp : m_pRectangles)
    {
        temp->draw(target, states);
    }
    for (auto& temp : m_pBalls)
    {
        temp->draw(target, states);
    }

    m_pDoor->draw(target, states);
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

void Game::onMousePressed(sf::Mouse::Button button, int mouseX, int mouseY)
{
    m_pGameInput->onMousePressed(button, mouseX, mouseY);
}

void Game::onMouseReleased(sf::Mouse::Button button)
{
    m_pGameInput->onMouseReleased(button);
}

void Game::onMouseMove(int mouseX, int mouseY)
{
    m_pGameInput->onMouseMove(mouseX, mouseY);
}

void Game::throwBall(InputData inputData, float deltaTime)
{

    if (m_ballCount > 0 && m_ballThrowDelay == 0.0f)
    {
        sf::Vector2f playerPos = m_pPlayer->getCenter();

        float x1 = playerPos.x;
        float y1 = playerPos.y;
        float x2 = inputData.m_mouseX;
        float y2 = inputData.m_mouseY;

        float speed = Gravity;

        float deltaX = x2 - x1;
        float deltaY = y2 - y1;

        float magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);

        sf::Vector2f Velocity((deltaX / magnitude) * speed, (deltaY / magnitude) * speed);

        m_pBalls.push_back(std::make_unique<Ball>(this, BallRadius, playerPos, Velocity));
        m_ballCount--;
        m_ballReloadTime = 5.0f;
        m_ballThrowDelay = BallThrowDelay;
    }
}

void Game::updateBallDelays(float deltaTime)
{
    if (m_ballCount < BallMaxCount)
    {
        m_ballReloadTime -= deltaTime;
        if (m_ballReloadTime < 0.0f)
        {
            m_ballCount++;
            m_ballReloadTime = 5.0f;
        }
    }
    m_ballThrowDelay -= deltaTime;
    if (m_ballThrowDelay < 0.0f)
    {
        m_ballThrowDelay = 0.0f;
    }
}

void Game::updateBallPhysics(float deltaTime)
{
    int i = 0;
    while (i < m_pBalls.size())
    {
        m_pBalls[i]->updatePhysics(deltaTime);
        if (m_pBalls[i]->isDead())
        {
            std::swap(m_pBalls[i], m_pBalls.back());
            m_pBalls.pop_back();
            continue;
        }
        i++;
    }
}

std::vector<Coin*> Game::getCoins() const
{
    std::vector<Coin*> pCoins;

    for (auto& temp : m_pCoins)
    {
        pCoins.push_back(temp.get());
    }
    return pCoins;
}

std::vector<Ball*> Game::getBalls() const
{
    std::vector<Ball*> pBalls;

    for (auto& temp : m_pBalls)
    {
        pBalls.push_back(temp.get());
    }
    return pBalls;
}

std::vector<Rectangle*> Game::getRectangles() const
{
    std::vector<Rectangle*> pRectangles;

    for (auto& pRectangle : m_pRectangles)
    {
        pRectangles.push_back(pRectangle.get());
    }
    return (pRectangles);
}

Door* Game::getDoor() const
{
    return m_pDoor.get();
}
