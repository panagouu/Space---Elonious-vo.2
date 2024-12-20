#include <sgg/graphics.h>
#include <iostream>

#include "GameState.h"
#include "Weapon.h"
#include "Player.h"


void Weapon::init()
{
	m_width = 0.4f;
	m_height = 0.4f;

	/* Initially set the x and the y so that the weapon is displayed by the player */
	m_pos_x = m_state->getPlayer()->m_pos_x + 0.4f;
	m_pos_y = m_state->getPlayer()->m_pos_y;

	m_brush_weapon.fill_opacity = 1.0f;
	m_brush_weapon.outline_opacity = 0.0f;
	m_brush_weapon.texture = m_state->getFullAssetPath("laserbullet.png");
}

void Weapon::draw()
{
	graphics::drawRect( m_pos_x, m_pos_y, m_width, m_height, m_brush_weapon);
	
	graphics::resetPose();
}

void Weapon::update(float dt)
{
	float delta_time =  dt / 1000.0f;
	m_pos_x += delta_time * velocity;

	if (m_pos_x > 2 * m_state->getCanvasWidth()) { m_active = false; }
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

