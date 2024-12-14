#include "GameState.h"
#include "util.h"
#include "Level.h"
#include "Player.h"
#include "Meteorite.h"

GameState::GameState()
{
}

void GameState::init()
{
	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("SpaceCraft");
	m_player->init();

	graphics::setFont(std::string(m_asset_path) + "chrusty-rock.ttf");
	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()
{
	if (!m_current_level) { return; }

	m_current_level->draw();
}

void GameState::update(float dt)
{
	if (dt > 500) { return; }
	if (!m_current_level) { return; }

	m_current_level->update(dt);
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





