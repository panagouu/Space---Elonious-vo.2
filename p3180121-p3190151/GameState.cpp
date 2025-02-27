#include "GameState.h"
#include "util.h"
#include "Elon.h"
#include "Level.h"
#include "Button.h"
#include "Player.h"
#include "Portal.h"
#include "Meteorite.h"
#include <iostream>

GameState::GameState()
{
}

void GameState::init()
{
	level = Entry_Level;

	graphics::setFont(std::string(m_asset_path) + "Bruce.ttf");
	music = getAssetDir() + "futuristic-space.wav";
	graphics::playMusic(music, 0.5f, true, 2000);

	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("SpaceCraft");
	m_player->init();

	m_portal = new Portal("Alien");

	graphics::preloadBitmaps(getAssetDir());
}

void GameState::update(float dt)
{
	if (level == Entry_Level)
	{
		updateStartScreen(dt);
	}
	else if (level == Level1)
	{
		updateGameScreen(dt);
	}
	else if (level == Level2)
	{
		updateGameScreen(dt);
	}
	else if (level == Level3)
	{
		updateGameScreen(dt);
	}
	else if (level == Failure_Level)
	{
		updateFailureScreen(dt);
	}
	else if (level == Victory_Level)
	{
		updateVictoryScreen(dt);
	}
}

void GameState::updateStartScreen(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		temp_total_time = graphics::getGlobalTime();

		level = Level1;

		music = getAssetDir() + "slavic-cinematic-metal.mp3";
		graphics::playMusic(music, 0.5f, true, 2000);
	}
}

void GameState::updateGameScreen(float dt)
{
	if (dt > 500) { return; }
	if (!m_current_level) { return; }

	m_current_level->update(dt);
}

void GameState::updateFailureScreen(float dt)
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	if (ms.button_left_pressed && ms.cur_pos_y >= 500 && ms.cur_pos_y <= 600)
	{
		if (ms.cur_pos_x >= 350 && ms.cur_pos_x < 500)
		{
			sound = getAssetDir() + "click.mp3";
			graphics::playSound(sound, 1.0f, false);

			temp_total_time = graphics::getGlobalTime();

			m_current_level = new Level();
			m_current_level->init();

			m_player = new Player("SpaceCraft");
			m_player->init();

			m_portal = new Portal("Alien");

			level = Level1;

			music = getAssetDir() + "slavic-cinematic-metal.mp3";
			graphics::playMusic(music, 0.5f, true, 2000);
		}

		if (ms.cur_pos_x >= 500 && ms.cur_pos_x <= 650)
		{
			sound = getAssetDir() + "click.mp3";
			graphics::playSound(sound, 1.0f, false);

			graphics::destroyWindow();
		}
	}
}

void GameState::updateVictoryScreen(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		graphics::destroyWindow();
	}
}

void GameState::drawStartScreen()
{
	graphics::Brush brush_background;
	graphics::Brush brush_text;

	brush_background.outline_opacity = 0.0f;
	brush_background.texture = getFullAssetPath("background4.png");

	brush_text.fill_opacity = 1.0f;
	brush_text.outline_opacity = 0.0f;

	std::string info = "Welcome to Space Elonius";
	std::string start = "Press  ENTER  to start";
	graphics::drawText(1.5f, 2.0f, 0.5f, info, brush_text);
	graphics::drawText(3.0f, 6.0f, 0.35f, start, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);
}

void GameState::drawGameScreen()
{
	if (!m_current_level) { return; }
	if (m_player->m_active == false) 
	{ 
		sound = getAssetDir() + "fail.mp3";
		graphics::playSound(sound, 0.5f, false);

		createButtons();
		level = Failure_Level; 

		music = getAssetDir() + "space.mp3";
		graphics::playMusic(music, 1.0f, true, 2000);

		return;
	}

	if (m_portal && !m_portal->isActive()) 
	{ 
		score += m_player->total_score;

		if (level == Level1)
		{
			sound = getAssetDir() + "level-completed.wav";
			graphics::playSound(sound, 0.5f, false);

			temp_total_time = graphics::getGlobalTime();
			level = Level2;

			m_current_level = new Level();
			m_current_level->init();

			m_player = new Player("SpaceCraft");
			m_player->init();

			m_portal = new Portal("Alien");

			music = getAssetDir() + "slavic-cinematic-metal.mp3";
			graphics::playMusic(music, 0.5f, true, 2000);
		}
		else if (level == Level2)
		{
			sound = getAssetDir() + "level-completed.wav";
			graphics::playSound(sound, 0.5f, false);

			unsigned short new_health = m_player->getHealth();
			level = Level3;

			m_current_level = new Level();
			m_current_level->init();

			m_player = new Player("SpaceCraft");
			m_player->init();

			m_player->updateHealth(new_health);

			m_elon = new Elon("Elon");
			m_elon->init();

			sound = getAssetDir() + "evil-laugh.mp3";
			graphics::playSound(sound, 1.5f, true);

			music = getAssetDir() + "thrash-metal.mp3";
			graphics::playMusic(music, 0.5f, true, 2000);
		}
		 
	}

	if (level == Level3 && !m_elon->isActive())
	{
		graphics::stopMusic();
		level = Victory_Level;

		sound = getAssetDir() + "level-completed.wav";
		graphics::playSound(sound, 0.5f, false);

		return;
	}

	m_current_level->draw();
}

void GameState::drawFailureScreen()
{
	graphics::Brush brush_background;
	graphics::Brush brush_text;

	brush_background.outline_opacity = 0.0f;
	brush_background.texture = getFullAssetPath("background4.png");

	left->draw();
	right->draw();

	brush_text.fill_opacity = 1.0f;
	brush_text.outline_opacity = 0.0f;

	std::string info = "GAME OVER";
	std::string again = "PLAY AGAIN?";
	std::string yes = "YES";
	std::string no = "NO";

	graphics::drawText(2.0f, 4.0f, 1.0f, info, brush_text);
	graphics::drawText(3.85f, 5.5f, 0.5f, again, brush_text);
	graphics::drawText(4.5f, 6.0f, 0.4f, yes, brush_text);
	graphics::drawText(6.5f, 6.0f, 0.4f, no, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);

	left->draw();
	right->draw();
}

void GameState::drawVictoryScreen()
{
	graphics::Brush brush_background;
	graphics::Brush brush_text;

	brush_background.outline_opacity = 0.0f;
	brush_background.texture = getFullAssetPath("background4.png");

	brush_text.fill_opacity = 1.0f;
	brush_text.outline_opacity = 0.0f;

	std::string info = "VICTORY";
	std::string all_scores = "SCORE:     " + std::to_string(score);
	graphics::drawText(3.0f, 4.0f, 1.0f, info, brush_text);
	graphics::drawText(4.3f, 5.5f, 0.4f, all_scores, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);
}

void GameState::createButtons()
{
	right = new Button("Right");
	left = new Button("Left");

	right->init();
	left->init();

	right->m_pos_x = 5.1f;
	right->m_pos_y = 5.8f;

	left->m_pos_x = 6.85f;
	left->m_pos_y = 5.8f;
}

void GameState::draw()
{
	if (level == Entry_Level)
	{
		drawStartScreen();
	}
	else if (level == Level1)
	{
		drawGameScreen();
	}
	else if (level == Level2)
	{
		drawGameScreen();
	}
	else if (level == Level3)
	{
		drawGameScreen();
	}
	else if (level == Failure_Level)
	{
		drawFailureScreen();
	}
	else if (level == Victory_Level)
	{
		drawVictoryScreen();
	}
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {  m_unique_instance = new GameState(); }
	return m_unique_instance;

}

GameState::~GameState()
{ 
	if (m_player) { delete m_player; }

	if (m_current_level) { delete m_current_level;  }
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

GameState* GameState:: m_unique_instance = nullptr;