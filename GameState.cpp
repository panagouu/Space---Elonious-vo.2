#include "GameState.h"
#include "util.h"
#include "Level.h"
#include "Player.h"
#include "Meteorite.h"

GameState::GameState()
{
}

void GameState::updateStartScreen(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		level = Level1;
		std::string music = getAssetDir() + "slavic-cinematic-metal.mp3";
		graphics::playMusic(music, 0.5f, true, 4000);
	}
}

void GameState::updateGameScreen(float dt)
{
	//if (dt > 500) { return; }
	if (!m_current_level) { return; }

	m_current_level->update(dt);
}

void GameState::updateFailureScreen(float dt)
{
}

void GameState::updateVictoryScreen(float dt)
{
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
	std::string start = "Press SPACE to start";
	graphics::drawText(1.5f, 2.0f, 0.5f, info, brush_text);
	graphics::drawText(3.0f, 6.0f, 0.35f, start, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);
}

void GameState::drawGameScreen()
{
	if (!m_current_level) { return; }
	if (m_player->m_active == false) 
	{ 
		std::string music = getAssetDir() + "fail-jingle.mp3";
		graphics::playMusic(music, 0.5f, false);
		level = Failure_Level;  
	}
	if (m_player->total_score > 200) 
	{ 
		std::string music = getAssetDir() + "level-completed.wav";
		graphics::playMusic(music, 0.5f, false);
		level = Victory_Level; 
	}
	m_current_level->draw();
}

void GameState::drawFailureScreen()
{
	graphics::Brush brush_background;
	graphics::Brush brush_text;

	brush_background.outline_opacity = 0.0f;
	brush_background.texture = getFullAssetPath("background4.png");

	brush_text.fill_opacity = 1.0f;
	brush_text.outline_opacity = 0.0f;

	std::string info = "GAME OVER";
	graphics::drawText(4.0f, 4.0f, 0.5f, info, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);
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
	graphics::drawText(4.0f, 4.0f, 0.5f, info, brush_text);
	graphics::drawRect(6.0f, 4.0f, 12.0f, 8.0f, brush_background);
}

void GameState::init()
{
	level = Entry_Level;

	graphics::setFont(std::string(m_asset_path) + "Bruce.ttf");
	std::string music = getAssetDir() + "futuristic-space.wav";
	graphics::playMusic(music, 0.5f, true, 2000);

	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("SpaceCraft");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
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
	else if (level == Failure_Level)
	{
		drawFailureScreen();
	}
	else if (level == Victory_Level)
	{
		drawVictoryScreen();
	}
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
	else if (level == Failure_Level)
	{

	}
	else if (level == Victory_Level)
	{

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





