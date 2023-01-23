#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow_Header.h"

class SettingsMenu {
	int pos;
	bool clicked, hovered;

	
	GameWindow gameWin;

	sf::Font* font;

	sf::Texture* bgImage;
	sf::Sprite* background;

	std::vector<sf::Texture> texButtons;
	std::vector<sf::Texture> texButtonHighlighted;
	std::vector<sf::Texture> texButtonPressed;
	
	sf::Sprite* sprButtonBack;

	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;

	std::vector<sf::Vector2f> buttonCoords;


protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	SettingsMenu();
	~SettingsMenu();
	void open_settings(GameWindow* gameWindow);
	
	
};