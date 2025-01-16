#include <sgg/graphics.h>
#include <iostream>
#include <random>

#include "GameState.h"
#include "Spacecraft.h"

void Spacecraft::init()
{
	current_health = 1;
	points = 5;
	dynamic = 2;
	shoot_timer = 600.f;
	t_reset_val = 600.f;

	m_width = 0.7f;
	m_height = 0.7f;

	/* Generate random numbers for the coordinates x and y of the spacecraft */
	m_pos_x = m_state->getCanvasWidth() + size;
	m_pos_y = ((float)rand() / RAND_MAX) * (m_state->getCanvasHeight() - 1.0f);

	/* Find upper and lower limit for specific spacecraft + set starting movement orientation (UP or DOWN) */
	if (m_pos_y - 3.f < 2 * size)
	{
		up_limit = 2 * size;
		low_limit = m_pos_y + 6.f - (m_pos_y - 2 * size);
		orient_point = 0;
	}
	else {
		if (m_pos_y + 3.f > m_state->getCanvasHeight() - size) {
			up_limit = m_pos_y - 6.f - (m_state->getCanvasHeight() - size - m_pos_y);
			low_limit = m_state->getCanvasHeight() - size;
			orient_point = 1;
		}
		else {
			up_limit = m_pos_y - 3.f;
			low_limit = m_pos_y + 3.f;
		}
	}	

	/* Brush of the spacecraft */
	m_brush_spacecraft.fill_opacity = 1.0f;
	m_brush_spacecraft.outline_opacity = 0.0f;
	m_brush_spacecraft.texture = m_state->getFullAssetPath("spacecraft-enemy.png");

}

void Spacecraft::update(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_x -= delta_time * velocity / 1.5f;

	shoot_timer -= dt;	// Update timer for next Bullet

	/* If intstance has passed canvas limit or has no more health deactivate it */
	if (m_pos_x < 0 || current_health == 0) { m_active = false; }

	/* 
	*  orient_point = 0 -> Moving DOWN, orient_point = 1 -> Moving UP
	*  When moving down, if low_limit hasn't been reached keep moving down else change orientation to start moving up
	*  When moving up, if up_limit hasn't been reached keep moving up else change orientation to start moving down
	*/
	if (orient_point == 0) {
		if (m_pos_y < low_limit) {
			m_pos_y += delta_time * velocity / 2.0f;
		}
		else {
			orient_point = 1;
		}
	}
	else if (orient_point == 1) {
		if (m_pos_y > up_limit) {
			m_pos_y -= delta_time * velocity / 2.0f;
		}
		else {
			orient_point = 0;
		}
	}
	
}

void Spacecraft::draw()
{
	graphics::setOrientation(rotation);
	graphics::drawRect(m_pos_x, m_pos_y, size, size, m_brush_spacecraft);

	graphics::resetPose();
}

void Spacecraft::debugDraw()
{
}