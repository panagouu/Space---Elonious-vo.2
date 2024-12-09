#include "Star.h"
#include "GameState.h"
#include <ctime>  
#include <iostream>

void Star::update(float dt)
{
}

void Star::init()
{
	/* Generate random numbers for the coordinates x and y of the stars */

	int random_width = (std::rand() % (3*(int)m_state->getCanvasWidth()) + 1) - (int)m_state->getCanvasWidth();
	int random_height = std::rand() % ((int)m_state->getCanvasHeight() + 1);
	
	std::cout << "width: " << random_width;
	std::cout << "heigth: " << random_height;

	m_pos_x = random_width;
	m_pos_y = random_height;

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
