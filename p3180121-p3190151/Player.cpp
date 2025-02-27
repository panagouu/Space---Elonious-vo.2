#include <sgg/graphics.h>
#include <iostream>

#include "Player.h"
#include "GameState.h"
#include "util.h"

void Player::update(float dt)
{
	if (current_health == 0) { m_active = false; }

	float delta_time =  dt / 1000.0f;
	const float velocity = 6.0f; 

	/* Change the x and the y variables of the player */
	if (graphics::getKeyState(graphics::SCANCODE_A)) { m_pos_x -= delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_D)) { m_pos_x += delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_W)) { m_pos_y -= delta_time * velocity; }
	if (graphics::getKeyState(graphics::SCANCODE_S)) { m_pos_y += delta_time * velocity; }

	/* Change the direction of the player */
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-left.png"); direction = Left; }
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-right.png"); direction = Right; }
	if (graphics::getKeyState(graphics::SCANCODE_UP)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-up.png"); direction = Up; }
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) { m_brush_player.texture = m_state->getFullAssetPath("spaceship-down.png"); direction = Down; }

	/* Restrict the player from going outside the background */
	if (m_pos_x < 0.5f) { m_pos_x = 0.5; }
	if (m_pos_x > 11.5f) { m_pos_x = 11.5; }

	if (m_pos_y < 0.5) { m_pos_y = 0.5; }
	if (m_pos_y > 7.5f) { m_pos_y = 7.5f; }

	drawScore();
	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = m_state->getCanvasWidth() / 2.0f;
	m_pos_y = m_state->getCanvasHeight() / 2.0f;

	direction = Right;
	current_health = 10;

	/* Brush of the player */
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state-> getFullAssetPath("spaceship-right.png");
}

void Player::draw()
{
	graphics::drawRect(m_pos_x , m_pos_y, 1.0f, 1.0f, m_brush_player);
	
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

void Player::drawScore()
{
	/* Brush of player's score */
	m_brush_score.fill_opacity = 1.0f;
	m_brush_score.outline_opacity = 0.0f;

	std::string info = "SCORE " + std::to_string(total_score);
	graphics::drawText(10, 0.5, 0.25, info, m_brush_score);
}

float Player::getX() 
{
	return m_pos_x;
}

float Player::getY()
{
	return m_pos_y;
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
