#pragma once
#include <sgg/graphics.h>
#include <string>
#include "Box.h"
#include "GameObject.h"
#include "Bullet.h"

class Spacecraft : public GameObject
{
    graphics::Brush m_brush_spacecraft;

    float velocity = 8.0f;
    float size = 0.8f;
    float rotation;
    float sh_timer = 0.0f;
    unsigned int orient_point;
    unsigned float up_limit;
    unsigned float low_limit;

    std::vector<Bullet*> bullets;

public:

    void update(float dt) override;
    void init() override;
    void draw() override;

    Spacecraft(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
};