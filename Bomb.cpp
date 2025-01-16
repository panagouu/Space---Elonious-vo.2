#include <sgg/graphics.h>
#include <iostream>
#include <random>

#include "GameState.h"
#include "Bomb.h"

void Bomb::update(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_x -= delta_time * velocity / 2.0f;

	if (m_pos_x < 0 || current_health == 0) { m_active = false; }
}

void Bomb::init()
{
	/* Generate random numbers for the coordinates x and y of the weapons */
	m_pos_x = m_state->getCanvasWidth() + 2.0f;
	m_pos_y = ((float)rand() / RAND_MAX) * (m_state->getCanvasHeight() - 0.5f);

	current_health = 4;
	points = 15;
	dynamic = 2;

	m_width = 1.8f;
	m_height = 1;

	/* Brush of the meteorite */
	m_brush_bomb.fill_opacity = 1.0f;
	m_brush_bomb.outline_opacity = 0.0f;
	m_brush_bomb.texture = m_state->getFullAssetPath("nuclear-left.png");

}

void Bomb::draw()
{
	graphics::setOrientation(rotation);
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_bomb);

	graphics::resetPose();
}

void Bomb::debugDraw()
{
}
