#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Weapon.h"
#include "GameObject.h"

/**
 * The Meteorite class implements one of the player's opponents, which  is the final enemy of the game 
 * that the player must defeat to finish the game..
 *
 */

class Elon : public GameObject
{
    graphics::Brush m_brush_elon;
    float velocity;

public:

    unsigned short total_score = 0;

    void update(float dt) override;
    void init() override;
    void draw() override;

    float getX();
    float getY();
    unsigned short getHealth() { return current_health; }
    Elon(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
 
};


