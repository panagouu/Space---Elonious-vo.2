#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Gameobject.h"

/**
 * The Bullet class generally implements the weapon that the final enemy uses to attack the player
 * and includes some basic functions for planning and maintaining his position.
 *
 */

class Bullet : public GameObject
{
    graphics::Brush m_brush_bullet;

    const float velocity = 12.0f;

public:

    void init() override;
    void draw() override;
    void update(float dt) override;

    Bullet(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};
