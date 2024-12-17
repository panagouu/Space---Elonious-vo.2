#pragma once

#include "box.h"
#include "gameobject.h"
#include <sgg/graphics.h>
#include <string>

class Meteorite : public GameObject, public Box
{
    graphics::Brush m_brush_meteorite;
    std::vector<std::string> m_sprites;

    const float velocity = 6.0f;
    float size;
    float rotation;

public:

    unsigned short current_health = 2;
    bool has_collided = false;

    void update(float dt) override;
    void init() override;
    void draw() override;

    Meteorite(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};

