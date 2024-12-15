#include <sgg/graphics.h>
#include "GameState.h"
#include "Meteorite.h"
#include "util.h"
#include <iostream>
#include <random>

void Meteorite::update(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_x -= delta_time * velocity / 2.0f;

	rotation += 0.4f * dt;
	rotation = fmodf(rotation, 360);

	if (m_pos_x < -5.0f || current_health == 0 ) { m_active = false; }
}

void Meteorite::init()
{
	/* Generate random numbers for the coordinates x and y of the weapons */
	m_pos_x = 2 * (m_state->getCanvasWidth()) + 5;
	m_pos_y = m_state->getCanvasHeight() * rand() / (float)RAND_MAX;

	/* Generate random numbers for the size and the rotation of the weapons */
	size = 0.5 + rand() / (float)RAND_MAX;
	rotation = 360 * rand() / (float)RAND_MAX;

	/* Brush of the meteorite */
	m_brush_meteorite.fill_opacity = 1.0f;
	m_brush_meteorite.outline_opacity = 0.0f;
	m_brush_meteorite.texture = m_state->getFullAssetPath("rock-enemy.png");

}

void Meteorite::draw()
{
	graphics::setOrientation(rotation);
	graphics::drawRect(m_state->m_global_offset_x + m_pos_x, m_state->m_global_offset_y + m_pos_y, size, size, m_brush_meteorite);

	graphics::resetPose();
}

void Meteorite::debugDraw()
{
}
