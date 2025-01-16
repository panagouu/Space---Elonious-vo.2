#include <sgg/graphics.h>
#include <iostream>

#include "GameState.h"
#include "Bullet.h"
#include "Elon.h"

void Bullet::init()
{
	if (m_name == "Spacecraft")
	{
		m_width = 0.5f;
		m_height = 0.5f;

		velocity = 12.0f;
		dynamic = 1;

		m_brush_bullet.fill_opacity = 1.0f;
		m_brush_bullet.outline_opacity = 0.0f;
		m_brush_bullet.texture = m_state->getFullAssetPath("laser_enemy-left.png");
	}
	else if (m_name == "Elon")
	{
		m_width = 0.5f;
		m_height = 0.5f;

		dynamic = 2;

		m_brush_bullet.fill_opacity = 1.0f;
		m_brush_bullet.outline_opacity = 0.0f;
		m_brush_bullet.texture = m_state->getFullAssetPath("laser_enemy-down.png");
	}

}

void Bullet::update(float dt)
{
	float delta_time = dt / 1000.0f;

	if (m_name == "Spacecraft")
	{
		m_pos_x -= delta_time * velocity;

		if (m_pos_x < 0) { m_active = false; }
	}
	else if (m_name == "Elon")
	{
		m_pos_y += delta_time * velocity;

		if (m_pos_y > 2 * m_state->getCanvasHeight()) { m_active = false; }
	}

	
}

void Bullet::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_bullet);

	graphics::resetPose();
}

void Bullet::debugDraw()
{
}