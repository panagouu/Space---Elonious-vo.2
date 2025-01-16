#include <iostream>

#include "Level.h"
#include "Elon.h"
#include "GameState.h"
#include "Player.h"
#include "Meteorite.h"
#include "Portal.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Bomb.h"
#include "Star.h"

Level::Level(const std::string& name)
{
}

void Level::update(float dt)
{
	/* Update variables for background */
	float delta_time = dt / 1000.0f;
	const float velocity = 5.0f;

	if (graphics::getGlobalTime() - m_state->getTotalTime() <= 30000 && m_state->getLevel() != 3) {
		/* Update x position for background & distance covered by current background */
		offset_x -= delta_time * velocity;
		bkgnd_dist += delta_time * velocity;

		/* If current background has cover a distance equal to its width
			print a new background */
		if (bkgnd_dist >= m_state->getCanvasWidth() * 4.0f)
		{
			/* Background distance starts counting from 0 */
			bkgnd_dist = 0;

			switch (flag) {
			case 0:
				x0 = x2 + m_state->getCanvasWidth() * 4;
				flag = 1;
				break;
			case 1:
				x1 = x0 + m_state->getCanvasWidth() * 4;
				flag = 2;
				break;
			case 2:
				x2 = x1 + m_state->getCanvasWidth() * 4;
				flag = 0;
				break;
			}
		}
	}

	time_passed += dt; 

	if (m_state->getLevel() == 3)
	{
		m_state->getElon()->update(dt);
	}

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->update(dt);
	}

	createEnemy();

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

	/* Update the elements of the dynamic_objects vector that are active  */
	for (auto p : m_enemy_objects)
	{
		if (p) { p->update(dt); }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { p->update(dt); }
	}

	for (auto p : m_bullet_objects)
	{
		if (p) { p->update(dt); }
	}

	for (auto p : m_static_objects)
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

	/* Create 10 stars for when the player loses lives and wants to regain them */
	if (m_state->getLevel() != 3)
	{
		Star* star = 0;
		for (int i = 0; i < 10; i++)
		{
			star = new Star("star" + i);
			m_static_objects.push_back(star);
		}
	}

	for (auto p : m_static_objects) 
	{
		if (p) { p->init(); }
	}

	for (auto p : m_enemy_objects)
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
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	graphics::drawRect(offset_x + x0, offset_y, w * 4.0f, h * 2.0f, m_brush_back);
	graphics::drawRect(offset_x + x1, offset_y, w * 4.0f, h * 2.0f, m_brush_back);
	graphics::drawRect(offset_x + x2, offset_y, w * 4.0f, h * 2.0f, m_brush_back);

	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->draw();
		m_state->getPlayer()->drawHealth();
		m_state->getPlayer()->drawScore();
	}

	if (m_state->getLevel() == 1)
	{
		if (graphics::getGlobalTime() - m_state->getTotalTime() > 30000 && m_state->getPortal()->isActive())
		{
			m_state->getPortal()->init();
			m_state->getPortal()->draw();
		}
	}
	else if (m_state->getLevel() == 2 )
	{
		if (graphics::getGlobalTime() - m_state->getTotalTime() > 30000 && m_state->getPortal()->isActive())
		{
			m_state->getPortal()->init();
			m_state->getPortal()->draw();
		}
	} else 
	{ 
		m_state->getElon()->draw(); 
	}

	for (auto p : m_static_objects)
	{
		if (p) { p->draw(); }
	}

	for (auto p : m_enemy_objects)
	{
		if (p) { p->draw(); }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { p->draw(); }
	}

	for (auto p : m_bullet_objects)
	{
		if (p) { p->draw(); }
	}
}

void Level::checkCollision()
{
	/* Check if the player collides with a Meteorite and reduce his health by the dynamic of meteorite */
	for (auto& meteorite : m_enemy_objects)
	{
		if (m_state->getPlayer()->intersect(*meteorite))
		{
			if (!(meteorite->has_collided))
			{
				m_state->getPlayer()->current_health -= meteorite->dynamic;
				meteorite->has_collided = true;
				meteorite->m_active = false;
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
			}

		}
	}

	/* Check if an object Weapon hits an object Meteorite */
	for (auto& weapon : m_weapon_objects) {
		for (auto& meteorite : m_enemy_objects) {
			if (weapon->intersect(*meteorite)) {
				if (!meteorite->has_collided)
				{
					meteorite->has_collided = true;
					meteorite->current_health--;

					m_state->getPlayer()->total_score += meteorite->points;
					weapon->m_active = false;
				}
			}
			else {
				meteorite->has_collided = false;
			}
		}
	}

	/* Check if an object Weapon hits the object Elon */
	for (auto& weapon : m_weapon_objects) {
		if (m_state->getElon() && weapon->intersect(*m_state->getElon()))
		{
			m_state->getElon()->current_health--;

			m_state->getPlayer()->total_score += m_state->getElon()->points;
			weapon->m_active = false;

		}
	}

	/* Check if an object Bullet hits the player */
	for (auto& bullet : m_bullet_objects) {
		if (bullet->intersect(*m_state->getPlayer()))
		{
			if (!bullet->has_collided)
			{
				bullet->has_collided = true;
				bullet->m_active = false;
				m_state->getPlayer()->current_health -= bullet->dynamic;
			}
		}
		else { 
			bullet->has_collided = false; 
		}
	}

	/* Check if the player collides with the Portal and move the player to the next level */
	if (m_state->getPlayer()->intersect(*m_state->getPortal()))
	{
		m_state->getPortal()->m_active = false;
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

	for (GameObject* p : m_enemy_objects)
	{
		if (p && !p->isActive()) 
		{
			/* delete the object p from the vector m_enemy_objects */
			m_enemy_objects.erase(std::remove(m_enemy_objects.begin(), m_enemy_objects.end(), p), m_enemy_objects.end());

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

	for (GameObject* p : m_bullet_objects)
	{
		if (p && !p->isActive())
		{
			/* delete the object p from the vector m_bullet_objects */
			m_bullet_objects.erase(std::remove(m_bullet_objects.begin(), m_bullet_objects.end(), p), m_bullet_objects.end());

			delete p;
			p = nullptr;
		}
	}
}

void Level::createEnemy()
{
	if (m_state->getLevel() == 1)
	{
		/* Create an object Meteorite, add it to the enemy vector */
		if (time_passed >= m_next_met)
		{
			Meteorite* m = new Meteorite("");
			m_enemy_objects.push_back(m);
			m->init();

			/* Calculate a random time that need to pass before the next one appears */
			time_passed = 0;
			m_next_met = static_cast <float>(900 + (rand() % 2001));
		}
	}
	else if (m_state->getLevel() == 2)
	{
		/* Create an object Bomb, add it to the enemy vector */
		if (time_passed >= m_next_met)
		{
			Bomb* b = new Bomb("");
			m_enemy_objects.push_back(b);
			b->init();

			std::string sound = m_state->getAssetDir() + "bomb.wav";
			graphics::playSound(sound, 3, false);

			/* Calculate a random time that need to pass before the next one appears */
			time_passed = 0;
			m_next_met = static_cast <float>(900 + (rand() % 2001));
		}
	}
	else if (m_state->getLevel() == 3)
	{
		/* Create an object Bomb, add it to the enemy vector */
		if (time_passed >= m_next_met)
		{
			Meteorite* m = new Meteorite("");
			m_enemy_objects.push_back(m);
			m->init();

			Bullet* bullet = new Bullet("Bullet");
			m_bullet_objects.push_back(bullet);

			bullet->init();

			/* Calculate a random time that need to pass before the next one appears */
			time_passed = 0;
			m_next_met = static_cast <float>(900 + (rand() % 1001));
		}
	}
}

Level::~Level()
{
	for (auto p : m_static_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_enemy_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_weapon_objects)
	{
		if (p) { delete p; }
	}

	for (auto p : m_bullet_objects)
	{
		if (p) { delete p; }
	}
}
