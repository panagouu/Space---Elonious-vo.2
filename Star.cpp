#include <random>  
#include <iostream>

#include "GameState.h"
#include "Star.h"


void Star::update(float dt)
{
	float delta_time = dt / 1000.0f;
	const float velocity = 5.0f;

	m_pos_x -= delta_time * velocity;
}

void Star::init()
{
	m_width = 0.5f;
	m_height = 0.5f;

	/* Generate random numbers for the coordinates x and y of the stars */
	m_pos_x = rand() / (float)RAND_MAX * m_state->getCanvasWidth() * 11.0f;
	m_pos_y = rand() / (float)RAND_MAX * (m_state->getCanvasHeight() - 0.5f);

	/* Brush of the star */
	m_brush_star.fill_opacity = 1.0f;
	m_brush_star.outline_opacity = 0.0f;
	m_brush_star.texture = m_state->getFullAssetPath("white-star.png");
}

void Star::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_star);

	graphics::resetPose();
}

void Star::debugDraw()
{
}
