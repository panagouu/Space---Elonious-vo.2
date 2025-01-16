#include <sgg/graphics.h>
#include <iostream>

#include "GameState.h"
#include "Bullet.h"
#include "Elon.h"

void Bullet::init()
{
	m_width = 0.5f;
	m_height = 0.5f;

	dynamic = 2;

	/* Initially set the x and the y so that the bullet is displayed by the Elon */
	m_pos_x = m_state->getElon()->m_pos_x;
	m_pos_y = m_state->getElon()->m_pos_y + 0.5f;

	m_brush_bullet.fill_opacity = 1.0f;
	m_brush_bullet.outline_opacity = 0.0f;
	m_brush_bullet.texture = m_state->getFullAssetPath("laser_enemy-down.png");
}

void Bullet::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_bullet);

	graphics::resetPose();
}

void Bullet::update(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_y += delta_time * velocity;

	if (m_pos_y > 2 * m_state->getCanvasHeight()) { m_active = false; }
}
