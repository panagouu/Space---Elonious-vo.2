#include "Star.h"
#include "GameState.h"
#include <random>  
#include <iostream>

void Star::update(float dt)
{
}

void Star::init()
{
	/* Generate random numbers for the coordinates x and y of the stars */
	m_pos_x = rand() / (float)RAND_MAX * 6 * m_state->getCanvasWidth();
	m_pos_y = rand() / (float)RAND_MAX * m_state->getCanvasHeight();

	/* Brush of the star */
	m_brush_star.fill_opacity = 1.0f;
	m_brush_star.outline_opacity = 0.0f;
	m_brush_star.texture = m_state->getFullAssetPath("white-star.png");
}

void Star::draw()
{
	graphics::drawRect(m_state->m_global_offset_x + m_pos_x, m_state->m_global_offset_y + m_pos_y,
					0.5f, 0.5f, m_brush_star);

	graphics::resetPose();
}

void Star::debugDraw()
{
}
