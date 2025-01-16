#pragma once
#include <string>

#include "Box.h"

/**
 * The GameObject class generally organizes basic functions and features that each game entity needs 
 * to implement and have.
 *
 */

class GameObject: public Box 
{
	static int m_next_id; 

protected:

	class GameState* m_state;
	std::string m_name;

	float t_reset_val = 200.f;
	int m_id = 0;

public:

	bool m_active = true;
	bool has_collided = false;
	float shoot_timer = 200.f;

	unsigned short current_health;
	unsigned short points;
	unsigned short dynamic;

	void resetShootTimer() { shoot_timer = t_reset_val; }
	std::string getName() { return m_name; }

	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}

	virtual ~GameObject() {}

	bool isActive() { return m_active; }
	GameObject(const std::string& name = "");
};
