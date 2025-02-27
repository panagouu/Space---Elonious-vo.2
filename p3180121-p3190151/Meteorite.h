#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Gameobject.h"

/**
 * The Meteorite class implements one of the player's opponents, which is the meteorite.
 *
 */

class Meteorite : public GameObject
{
    graphics::Brush m_brush_meteorite;

    const float velocity = 6.0f;
    float size;
    float rotation;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Meteorite(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};

