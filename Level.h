#pragma once

#include <sgg/graphics.h>
#include "GameObject.h"
#include <list>

class Level : public GameObject
{
	graphics::Brush m_brush_back;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	float m_next_met = 0.0f;
	float time_passed = 0.0f;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects; 

public:

	Level(const std::string& name = "Level0");
	void update(float dt)  override;
	void init()  override;
	void draw()  override;
	~Level();

};