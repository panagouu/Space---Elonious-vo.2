#include <sgg/graphics.h>
#include <iostream>

#include "GameState.h"
#include "Elon.h"

void Elon::update(float dt)
{
	float delta_time = dt / 1000.0f;

	// Change the velocity so that this entity comes and goes on the x-axis.
	if (m_pos_x <= 0.5f) { velocity = 8.0f; }
	if (m_pos_x >= m_state->getCanvasWidth()) { velocity = -8.0f; }

	m_pos_x += delta_time * velocity / 2.0f;

	if (current_health == 0) { m_active = false; }
}

void Elon::init()
{
	m_pos_x = 0.5f;
	m_pos_y = 0.5f;

	m_width = 1.0f;
	m_height = 1.0f;

	current_health = 10;
	points = 25;
	dynamic = 4;

	/* Brush of the Elon */
	m_brush_elon.fill_opacity = 1.0f;
	m_brush_elon.outline_opacity = 0.0f;
	m_brush_elon.texture = m_state->getFullAssetPath("elon4.png");

}

void Elon::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_elon);

	graphics::resetPose();
}

float Elon::getX()
{
	return m_pos_x;
}

float Elon::getY()
{
	return m_pos_y;
}
