#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Gameobject.h"

class Bullet : public GameObject
{
    graphics::Brush m_brush_bullet;

    float velocity = 10.0f;

public:

    void init() override;
    void draw() override;
    void update(float dt) override;

    Bullet(std::string name, float x, float y) : GameObject(name) { m_pos_x = x; m_pos_y = y; }

protected:

    void debugDraw();
};
