#include "GameState.h"
#include "Portal.h"


void Portal::update(float dt)
{
}

void Portal::init()
{
	m_pos_x = m_state->getCanvasWidth() / 2.0f + 3.0f;
	m_pos_y = m_state->getCanvasHeight() / 2.0f;

	/* Brush of the star */
	m_brush_portal.fill_opacity = 1.0f;
	m_brush_portal.outline_opacity = 0.0f;
	m_brush_portal.texture = m_state->getFullAssetPath("spaceship-alien.png");
}

void Portal::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, 1.0f, 1.0f, m_brush_portal);

	graphics::resetPose();
}

void Portal::debugDraw()
{
}