#pragma once

#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Gameobject.h"

/**
 * The Bomb class implements one of the player's opponents, which is the bomb.
 *
 */

class Bomb : public GameObject
{
    graphics::Brush m_brush_bomb;

    const float velocity = 15.0f;
    float size;
    float rotation;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Bomb(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};
