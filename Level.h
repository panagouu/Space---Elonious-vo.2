#pragma once
#include <sgg/graphics.h>
#include <list>

#include "Meteorite.h"
#include "GameState.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Star.h"

/**
 * The Level class generally implements the current level and holds all the game entities, handles background movement, 
 * controls collisions between the player and enemies.
 *
 */

class Level : public GameObject
{
	graphics::Brush m_brush_back;

	/* Variables for setting each background's position */
	int	flag = 0;
	float bkgnd_dist = 0.0f;
	float x0 = m_state->getCanvasWidth() * 0.0f;
	float x1 = m_state->getCanvasWidth() * 4.0f;
	float x2 = m_state->getCanvasWidth() * 8.0f;

	float offset_x = 0.0f;
	float offset_y = m_state->getCanvasHeight() / 2.0f;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	float m_next_met = 0.0f;
	float time_passed = 0.0f;

	/* The variable pressed_space prevents multiple Weapon objects from being created when pressing space once */
	bool pressed_space = false;
	bool passed_time = false;

	std::vector<Star*> m_static_objects;
	std::vector<GameObject*> m_enemy_objects;
	std::vector<Weapon*> m_weapon_objects;
	std::vector<Bullet*> m_bullet_objects;

	void checkCollision();
	void checkObjects();
	void createEnemy();

public:

	Level(const std::string& name = "Level");

	void update(float dt)  override;
	void init()  override;
	void draw()  override;

	~Level();

};