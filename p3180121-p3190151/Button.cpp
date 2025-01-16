#include "Button.h"
#include "GameState.h"

void Button::update(float dt)
{
}

void Button::init()
{
	m_width = 2.0f;
	m_height = 1.0f;

	/* Brush of the button */
	m_brush_button.fill_opacity = 1.0f;
	m_brush_button.outline_opacity = 0.0f;
	m_brush_button.texture = m_state->getFullAssetPath("button2.png");
}

void Button::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_button);

	graphics::resetPose();
}
