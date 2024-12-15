#pragma once

#include <string>
#include "sgg/graphics.h"

class GameState
{
	typedef enum {Entry_Level, Level1, Level2, Level3, Failure_Level, Victory_Level} m_level;
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 12.0f;
	float m_canvas_height = 8.0f;

	m_level level;
	static GameState* m_unique_instance;

	GameState();

	class Player * m_player = 0; 
	class Level* m_current_level = 0;

	void updateStartScreen(float dt);
	void updateGameScreen(float dt);
	void updateFailureScreen(float dt);
	void updateVictoryScreen(float dt);

	void drawStartScreen();
	void drawGameScreen();
	void drawFailureScreen();
	void drawVictoryScreen();

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

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() { return m_player; }
};
