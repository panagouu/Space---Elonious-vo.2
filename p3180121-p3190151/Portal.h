#pragma once
#include <sgg/graphics.h>
#include <string>

#include "GameObject.h"
#include "Box.h"

/**
 * The Portal class implements the gate of each level, which the player can pass through 
 * to go to the next level. It will be created only for the first and second level.
 *
 */

class Portal : public GameObject
{
    graphics::Brush m_brush_portal;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Portal(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};
