#pragma once

#include <sgg/graphics.h>
#include "GameObject.h"
#include "Meteorite.h"
#include "Weapon.h"
#include "Star.h"
#include <list>

class Level : public GameObject
{
	graphics::Brush m_brush_back;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	float m_next_met = 0.0f;
	float time_passed = 0.0f;

	/* The variable pressed_space prevents multiple Weapon objects from being created when pressing space once */
	bool pressed_space = false;

	std::vector<Star*> m_static_objects;
	std::vector<Meteorite*> m_meteorite_objects;
	std::vector<Weapon*> m_weapon_objects;

public:

	Level(const std::string& name = "Level");

	void update(float dt)  override;
	void init()  override;
	void draw()  override;

	void checkCollision();
	void checkObjects();
	~Level();

};