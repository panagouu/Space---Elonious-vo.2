#include "Weapon.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "util.h"
#include <iostream>
#include "Player.h"

void Weapon::init()
{
	/* Initially set the x and the y so that the weapon is displayed by the player */
	m_pos_x = (m_state->getCanvasWidth() * 0.5f) + 0.6f - m_state->m_global_offset_x;
	m_pos_y = m_state->getCanvasHeight() * 0.5f - m_state->m_global_offset_y;

	m_brush_weapon.fill_opacity = 1.0f;
	m_brush_weapon.outline_opacity = 0.0f;
	m_brush_weapon.texture = m_state->getFullAssetPath("laserbullet.png");
}

void Weapon::draw()
{
	graphics::drawRect(m_state->m_global_offset_x + m_pos_x, m_state->m_global_offset_y + m_pos_y, 0.4f, 0.4f, m_brush_weapon);
	
	graphics::resetPose();
}

void Weapon::update(float dt)
{
	float delta_time =  dt / 1000.0f;
	m_pos_x += delta_time * velocity;

	if (m_pos_x > 6 * m_state->getCanvasWidth() + 2.0f) { m_active = false; }
}

void Weapon::activate()
{
	m_active = true;
}

void Weapon::deactivate()
{
	m_active = false;
}

void Weapon::debugDraw()
{
}

