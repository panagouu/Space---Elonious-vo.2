#pragma once
#include <sgg/graphics.h>
#include <string>

#include "GameObject.h"
#include "Box.h"

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
