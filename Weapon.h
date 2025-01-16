#pragma once
#include <sgg/graphics.h>
#include <string>

#include "Box.h"
#include "Gameobject.h"

class Weapon : public GameObject
{
    graphics::Brush m_brush_weapon;

    typedef enum { Left, Right, Up, Down } m_direction;
    m_direction weapon_direction;

    const float velocity = 12.0f;

    public:

        void init() override;
        void draw() override;
        void update(float dt) override;

        void activate();
        void deactivate();

        Weapon(std::string name) :GameObject(name) {}

    protected:

        void debugDraw();
};

  
