#include "Meteorite.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "util.h"
#include <iostream>

void Meteorite::update(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_x -= delta_time * velocity / 2.0f;
}

void Meteorite::init()
{
	m_pos_x = m_state->getCanvasWidth() ;
	m_pos_y = rand() % (int)m_state->getCanvasHeight();

	/* Brush of the meteorite */
	m_brush_meteorite.fill_opacity = 1.0f;
	m_brush_meteorite.outline_opacity = 0.0f;
	m_brush_meteorite.texture = m_state->getFullAssetPath("rock-enemy.png");
}

void Meteorite::draw()
{
	graphics::drawRect(m_state->m_global_offset_x + m_pos_x, m_state->m_global_offset_y + m_pos_y, 1.0f, 1.0f, m_brush_meteorite);

	graphics::resetPose();
}

void Meteorite::debugDraw()
{
}
