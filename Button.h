#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Gameobject.h"
#include "Box.h"

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
