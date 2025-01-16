#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Gameobject.h"
#include "Box.h"

/**
 * The Button class implements the button at the level of failure, where the player can choose the options, 
 * play the game again from the beginning or end the game.
 *
 */

class Button : public GameObject
{
    graphics::Brush m_brush_button;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Button(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};
