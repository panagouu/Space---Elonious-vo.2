#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Gameobject.h"
#include "Box.h"

class Star : public GameObject
{
    graphics::Brush m_brush_star;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Star(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};