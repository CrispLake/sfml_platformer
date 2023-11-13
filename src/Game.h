#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>
#include "Constants.h"

class Player;
class Game;
class GameInput;
class Rectangle;
class Coin;
class Door;
class Ball;
class Button;

struct InputData;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
    };
    
    Game();
    ~Game();
    
    bool initialise(sf::Vector2f pitchSize);
    void update(float deltaTime);
    void resetLevel(const int tileMap[GridSize * GridSize]);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    void onMousePressed(sf::Mouse::Button button, int mouseX, int mouseY);
    void onMouseReleased(sf::Mouse::Button button);
    void onMouseMove(int mouseX, int mouseY);

    void throwBall(InputData inputData, float deltaTime);
    void updateBallDelays(float deltaTime);
    void updateBallPhysics(float deltaTime);

    Door*                   getDoor() const;
    std::vector<Rectangle*> getRectangles() const;
    std::vector<Coin*>      getCoins() const;
    std::vector<Ball*>      getBalls() const;
    std::vector<Button*>    getButtons() const;


private:
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<Door> m_pDoor;

    std::vector<std::unique_ptr<Rectangle>> m_pRectangles;
    std::vector<std::unique_ptr<Coin>> m_pCoins;

    std::vector<std::unique_ptr<Ball>> m_pBalls;
    std::vector<std::unique_ptr<Button>> m_pButtons;

    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;

    int m_clearedLevels;
    
    int m_score;

    int m_ballCount;
    float m_ballReloadTime;
    float m_ballThrowDelay;

    int m_buttonCount;
    
    sf::Font m_font;
};
