#pragma once

#include <string>
#include "sgg/graphics.h"

class GameState
{
	typedef enum {Entry_Level, Level1, Level2, Level3, Failure_Level, Victory_Level} m_level;
	std::string m_asset_path = "bin\\assets\\";
	std::string sound;
	std::string music;

	float m_canvas_width = 12.0f;
	float m_canvas_height = 8.0f;
	float temp_total_time = 0.0f;
	unsigned int score = 0;

	m_level level;
	static GameState* m_unique_instance;

	GameState();

	class Player * m_player = 0; 
	class Portal* m_portal = 0;
	class Elon* m_elon = 0;
	class Level* m_current_level = 0;
	class Button* left = 0;
	class Button* right = 0;

	void updateStartScreen(float dt);
	void updateGameScreen(float dt);
	void updateFailureScreen(float dt);
	void updateVictoryScreen(float dt);

	void drawStartScreen();
	void drawGameScreen();
	void drawFailureScreen();
	void drawVictoryScreen();

	void createButtons();

public:

	float m_global_offset_x = 0.0f; 
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }
	float getTotalTime() { return temp_total_time; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() { return m_player; }
	class Portal* getPortal() { return m_portal; }
	class Elon* getElon() { return m_elon; }


	m_level getLevel() { return level; }
};
