#include "InputHandler.h"
#include "Player.h"
#include "Game.h"

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{

    
}

GameInput::~GameInput()
{
    
}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }
    if (m_inputData.hasClick())
    {
        m_pGame->throwBall(m_inputData, deltaTime);
    }
    if (m_inputData.hasReset())
    {
        m_pGame->resetCurrentLevel();
    }
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_resetButton = true;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_resetButton = false;
    }
}

void GameInput::onMousePressed(sf::Mouse::Button button, float mouseX, float mouseY)
{
    if (button == sf::Mouse::Left)
    {
        m_inputData.m_leftClick = true;
        m_inputData.m_mouseX = mouseX;
        m_inputData.m_mouseY = mouseY;
    }
}

void GameInput::onMouseReleased(sf::Mouse::Button button)
{
    if (button == sf::Mouse::Left)
        m_inputData.m_leftClick = false;
}

void GameInput::onMouseMove(float mouseX, float mouseY)
{
    m_inputData.m_mouseX = mouseX;
    m_inputData.m_mouseY = mouseY;
}