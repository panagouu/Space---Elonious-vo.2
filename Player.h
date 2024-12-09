#pragma once
#include "box.h"
#include "gameobject.h"
#include <sgg/graphics.h>
#include <string>
#include "Weapon.h"

class Player : public GameObject, public Box
{
    graphics::Brush m_brush_player;
    graphics::Brush m_brush_lives;
    std::vector<GameObject> m_sprites;

    float x = 0;
    float y = 0;

    const float m_gravity = 10.0f;
    const float m_accel_vertical = 200.0f;
    const float m_accel_horizontal = 40.0f;
    const float m_max_velocity = 10.0f;

    void movePlayer(float dt);

public:

    float m_vx = 0.0f;
    float m_vy = 0.0f;
    unsigned short current_health = 10;

    void update(float dt) override;
    void init() override;
    void draw() override;

    void drawHealth();
    Player(std::string name) :GameObject(name) {}

protected:

    void debugDraw();
    unsigned short getHealth() { return current_health; }
    void updateHealth(unsigned short new_health) { current_health = new_health; }
};

