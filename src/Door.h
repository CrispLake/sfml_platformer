#pragma once

#include "Rectangle.h"

class Game;

class Door : public Rectangle
{
public:
    Door(Game* pGame);
    virtual ~Door() {}

    int getCoins() const { return m_coins; };

    void setTriggered(bool triggered) { m_isTriggered = triggered; } 
    bool isTriggered() const { return m_isTriggered; }

    void setOpen();
    void setLocked();
    bool isOpen() const { return m_isOpen; }

private:
    Game*   m_pGame;
    bool    m_isTriggered = false;
    bool    m_isOpen = true;
    int     m_coins = 0;
};
