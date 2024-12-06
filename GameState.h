#pragma once

#include <string>
#include "sgg/graphics.h"

class GameState
{
private: 
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 12.0f;
	float m_canvas_height = 8.0f;

	static GameState* m_unique_instance;

	GameState(); // εδω να διαχειριζετε τον παιχτη και τα λεβελ

	class Player * m_player = 0; // κυκλική εξάρτηση και στα δύο 
	class Level* m_current_level = 0;

public:
	float m_global_offset_x = 0.0f; 
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;
	class Weapon* m_weapon = 0;

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
	class Weapon* getWeapon() { return m_weapon; }
};
