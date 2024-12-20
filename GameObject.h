#pragma once
#include <string>

#include "Box.h"

class GameObject: public Box 
{
	static int m_next_id; 

protected:

	class GameState* m_state;
	std::string m_name;

	int m_id = 0;

public:

	bool m_active = true;
	bool has_collided = false;
	unsigned short current_health;

	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}

	virtual ~GameObject() {}

	bool isActive() { return m_active; }
	GameObject(const std::string& name = "");
};
