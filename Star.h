#pragma once
#include "box.h"
#include "gameobject.h"
#include <sgg/graphics.h>
#include <string>

class Star : public GameObject, public Box
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