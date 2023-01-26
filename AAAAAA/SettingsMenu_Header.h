#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class SettingsMenu {
	int pos;
	bool clicked, hovered;
	
	GameWindow gameWin;

	sf::Font* font;

	sf::Texture* bgImage;
	sf::Sprite* background;

	UI::Button pBackButton;
	
	std::vector<sf::Vector2f> buttonCoords;


protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	SettingsMenu();
	~SettingsMenu();
	bool settingsOpen;
	void open_settings(GameWindow* gameWindow);
	
	
};