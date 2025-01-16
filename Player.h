#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Weapon.h"
#include "GameObject.h"

/**
 * The Player class implements the unique player of the game and has methods for designing the player,
 * maintaining its position in the window, managing its lives, etc..
 *
 */

class Player : public GameObject
{
    graphics::Brush m_brush_player;
    graphics::Brush m_brush_lives;
    graphics::Brush m_brush_score;

    typedef enum { Left, Right, Up, Down } m_direction;
    m_direction direction;

public:

    unsigned short total_score = 0;

    void update(float dt) override;
    void init() override;
    void draw() override;

    void drawHealth();
    void drawScore();
    void updateScore(unsigned short new_score) { total_score = new_score; }

    unsigned short getHealth() { return current_health; }
    void updateHealth(unsigned short new_health) { current_health = new_health; }
    m_direction getDirection() { return direction; }

    float getX();
    float getY();
    Player(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};

