#pragma once
#include <string>

class GameObject
{
	static int m_next_id; 

protected:

	class GameState* m_state;
	std::string m_name;

	int m_id = 0;

public:

	GameObject(const std::string& name = "");
	bool m_active = true;

	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}

	bool isActive() { return m_active; }
};
