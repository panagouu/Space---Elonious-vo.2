#include "Level.h"
#include "GameState.h"
#include "Player.h"
#include "Meteorite.h"
#include "Weapon.h"
#include <iostream>
#include "Star.h"

Level::Level(const std::string& name)
{
}

void Level::update(float dt)
{
	time_passed += dt; 

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->update(dt);
	}

	/* An h lista einai adeia h einai h stigmh tou epomenou antikeimenou
		ftiakse enan metewrith, prosthese ton sth lista kai sxediase ton */
	if (time_passed >= m_next_met)
	{
		Meteorite* m = new Meteorite("");
		m_dynamic_objects.push_back(m);
		m->init();

		/* Ypologise enan tuxaio xrono pou prepei na perasei mexri na 
			emfanistei o epomenos metewriths */
		time_passed = 0;
		m_next_met = 900 + (rand() % 2001);
	}

	/* Create an object Weapon and add it to the dynamic objects */
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		Weapon* weapon = new Weapon("Laser");
		m_dynamic_objects.push_back(weapon);
		weapon->init();
		
	}

	/* Update the elements of the dynamic_objects vector that are active  */
	for (auto p : m_dynamic_objects)
	{
		if (p) { p->update(dt); }
	}

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_back.outline_opacity = 0.0f;
	m_brush_back.texture = m_state-> getFullAssetPath("background4.png");

	/* Create 10 stars for when the player loses lives and wants to regain them */
	Star* star = 0;
	for (int i = 0; i < 5; i++)
	{
		star = new Star("star" + i);
		m_static_objects.push_back(star);
	}

	for (auto p : m_static_objects) 
	{
		if (p) { p->init(); }
	}

	for (auto p : m_dynamic_objects)
	{
		if (p) { p->init(); }
	}
}

void Level::draw()
{
	float w = m_state-> getCanvasWidth();
	float h = m_state-> getCanvasHeight();

	float offset_x = m_state->m_global_offset_x + w / 2.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;

	graphics::drawRect(offset_x, offset_y, w * 4.0f, h * 2.0f, m_brush_back);

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->draw();
		m_state->getPlayer()->drawHealth();
	}

	for (auto p : m_static_objects)
	{
		if (p) { p->draw(); }
	}

	for (auto p : m_dynamic_objects)
	{
		if (p) { p->draw(); }
	}
}

Level::~Level()
{
	for (auto p : m_static_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_dynamic_objects)
	{
		if (p) { delete p; }
	}
}
