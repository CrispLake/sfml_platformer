#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class Player;
class Game;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;

    bool m_leftClick = false;
    float m_mouseX = 0.0f;
    float m_mouseY = 0.0f;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight;}
    bool hasClick() { return m_leftClick;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    void onMousePressed(sf::Mouse::Button button, float mouseX, float mouseY);
    void onMouseReleased(sf::Mouse::Button button);
    void onMouseMove(float mouseX, float mouseY);
    
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
};
