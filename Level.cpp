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

	/* Create an object Weapon and add it to the dynamic objects */
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		if (!pressed_space) 
		{
			std::string sound = m_state->getAssetDir() + "laser.wav";
			graphics::playSound(sound, 5, false);

			Weapon* weapon = new Weapon("Laser");
			m_weapon_objects.push_back(weapon);

			weapon->init();
			weapon->draw();

			pressed_space = true;
		}
	}
	else {
		pressed_space = false;
	}

	/* An h lista einai adeia h einai h stigmh tou epomenou antikeimenou
		ftiakse enan metewrith, prosthese ton sth lista kai sxediase ton */
	if (time_passed >= m_next_met)
	{
		Meteorite* m = new Meteorite("");
		m_meteorite_objects.push_back(m);
		m->init();

		/* Ypologise enan tuxaio xrono pou prepei na perasei mexri na 
			emfanistei o epomenos metewriths */
		time_passed = 0;
		m_next_met = static_cast < float>(900 + (rand() % 2001));
	}	

	/* Update the elements of the dynamic_objects vector that are active  */
	for (auto p : m_meteorite_objects)
	{
		if (p) { p->update(dt); }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { p->update(dt); }
	}

	checkCollision();
	checkObjects();
	
	GameObject::update(dt);
}

void Level::init()
{
	m_brush_back.outline_opacity = 0.0f;
	m_brush_back.texture = m_state-> getFullAssetPath("background4.png");

	//std::string music = m_state->getAssetDir() + "symphonic-metal.mp3";
	//graphics::playMusic(music, 0.5, true);

	/* Create 5 stars for when the player loses lives and wants to regain them */
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

	for (auto p : m_meteorite_objects)
	{
		if (p) { p->init(); }
	}

	for (auto p : m_weapon_objects)
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

	for (auto p : m_meteorite_objects)
	{
		if (p) { p->draw(); }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { p->draw(); }
	}
}

void Level::checkCollision()
{
	/* Check if the player collides with a Meteorite and reduce his health by one */
	for (auto& meteorite : m_meteorite_objects)
	{
		if (m_state->getPlayer()->intersect(*meteorite))
		{
			if (!(meteorite->has_collided))
			{
				m_state->getPlayer()->current_health--;
				meteorite->has_collided = true;
				std::cout << "h: " << m_state->getPlayer()->current_health;

				m_state->getPlayer()->m_pos_y += m_state->getPlayer()->intersectDown(*meteorite);
				m_state->getPlayer()->m_pos_x += m_state->getPlayer()->intersectSideways(*meteorite);
			}
		}
		else {
			meteorite->has_collided = false;
			
		}
	}

	/* Check if the player collides with a Star and increase his health by one, only if the player has less than 10 lives */
	if (m_state->getPlayer()->current_health < 10) 
	{
		for (auto& star : m_static_objects)
		{
			if (m_state->getPlayer()->intersect(*star))
			{
				star->m_active = false;
				m_state->getPlayer()->current_health++;

				std::string sound = m_state->getAssetDir() + "winning_health.wav";
				graphics::playSound(sound, 3, false);

				std::cout << "health: " << m_state->getPlayer()->current_health;
			}

		}
	}

	/* Check if an object Weapon hits an object Meteorite */
	for (auto* weapon : m_weapon_objects) {
		for (auto* meteorite : m_meteorite_objects) {
			if (weapon->intersect(*meteorite)) {
				if (!meteorite->has_collided)
				{
					meteorite->has_collided = true;
					meteorite->current_health--;

					m_state->getPlayer()->total_score = m_state->getPlayer()->total_score + 20;
					weapon->m_active = false;

					std::cout << "score: " << m_state->getPlayer()->total_score;
				}
				
			}
			else {
				meteorite->has_collided = false;
			}
		}
	}
}

void Level::checkObjects()
{
	for (GameObject* p : m_static_objects)
	{
		if (p && !p->isActive()) 
		{ 
			/* delete the object p from the vector m_static_objects */
			m_static_objects.erase(std::remove(m_static_objects.begin(), m_static_objects.end(), p), m_static_objects.end());

			delete p;
			p = nullptr;
		}
	}

	for (GameObject* p : m_meteorite_objects)
	{
		if (p && !p->isActive()) 
		{
			/* delete the object p from the vector m_meteorite_objects */
			m_meteorite_objects.erase(std::remove(m_meteorite_objects.begin(), m_meteorite_objects.end(), p), m_meteorite_objects.end());

			delete p;
			p = nullptr;
		}
	}

	for (GameObject* p : m_weapon_objects)
	{
		if (p && !p->isActive())
		{
			/* delete the object p from the vector m_weapon_objects */
			m_weapon_objects.erase(std::remove(m_weapon_objects.begin(), m_weapon_objects.end(), p), m_weapon_objects.end());
			
			delete p;
			p = nullptr;
		}
	}
}

Level::~Level()
{
	for (auto p : m_static_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_meteorite_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { delete p; }
	}
}
