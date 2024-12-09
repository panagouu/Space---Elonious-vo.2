#include "Player.h"
#include <sgg/graphics.h>
#include "GameState.h"
#include "util.h"
#include <algorithm>
#include <iostream>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;
	
	const float velocity = 10.f; 

	/* Change the x and the y variables of the player */
	if (graphics::getKeyState(graphics::SCANCODE_A)) { m_pos_x -= delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_D)) { m_pos_x += delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_W)) { m_pos_y -= delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_S)) { m_pos_y += delta_time * velocity; } 

	/* Change the direction of the player */
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-left.png"); }
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-right.png"); }
	if (graphics::getKeyState(graphics::SCANCODE_UP)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-up.png"); }
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-down.png"); }

	m_state-> m_global_offset_x = m_state-> getCanvasWidth() / 2.0f - m_pos_x;
	m_state-> m_global_offset_y = m_state-> getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	/* Brush of the player */
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state-> getFullAssetPath("spaceship-right.png");
}

void Player::draw()
{
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);
	
	graphics::resetPose();
}

void Player::drawHealth()
{
	/* Brush of player's health */
	m_brush_lives.fill_opacity = 1.0f;
	m_brush_lives.outline_opacity = 0.0f;
	m_brush_lives.texture = m_state->getFullAssetPath("white-star.png");

	for (int i = 0; i < current_health; i++) 
	{
		graphics::drawRect((m_state->getCanvasWidth() * 0.05f) + (i*0.35f), m_state->getCanvasHeight() * 0.035f,
			0.35f, 0.35f, m_brush_lives);
	}
}

void Player::movePlayer(float dt)
{
	//float delta_time = dt / 1000.0f;

	//// Stage 2 code: Acceleration-based velocity
	//float move = 0.0f;
	//if (graphics::getKeyState(graphics::SCANCODE_A))
	//	move -= 1.0f;
	//if (graphics::getKeyState(graphics::SCANCODE_D))
	//	move = 1.0f;

	//m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	//m_vx = std::max<float>(-m_max_velocity, m_vx);

	//// friction
	//m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	//// apply static friction threshold
	//if (fabs(m_vx) < 0.01f)
	//	m_vx = 0.0f;

	//// adjust horizontal position
	//m_pos_x += m_vx * delta_time;

	//// jump only when not in flight:
	//if (m_vy == 0.0f)
	//	m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;// not delta_time!! Burst 

	//// add gravity
	//m_vy += delta_time * m_gravity;

	//// adjust vertical position
	//m_pos_y += m_vy * delta_time;

}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth()*0.5f, m_state->getCanvasHeight()*0.5f, m_width, m_height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}
