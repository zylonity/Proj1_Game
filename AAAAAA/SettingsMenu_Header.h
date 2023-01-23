#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow_Header.h"

class SettingsMenu {
	
	GameWindow gameWin;

	sf::Font* font;
	sf::Texture* bgImage;
	sf::Sprite* background;



protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	SettingsMenu();
	~SettingsMenu();
	void open_settings(GameWindow* gameWindow);
	
	
};