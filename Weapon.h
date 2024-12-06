#pragma once
#include "box.h"
#include "gameobject.h"
#include <sgg/graphics.h>
#include <string>

class Weapon : public GameObject, public Box
{
    graphics::Brush m_brush_weapon;

    const float velocity = 20.0f;

    public:

        void init() override;
        void draw() override;
        void update(float dt) override;

        void activate();
        void deactivate();

        Weapon(std::string name) :GameObject(name) {}

    protected:
        //void debugDraw();
};

  
