#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class MainMenu {
	int pos;
	int buttonCount;
	bool clicked, hovered;

	GameWindow* gameWin;
	
	sf::Texture bgImage;
	sf::Texture logoImage;
	sf::Sprite background;
	sf::Sprite logo;
	

	UI::Button playButton;
	UI::Button settingsButton;
	UI::Button quitButton;

	std::vector<sf::Vector2f> buttonCoords;


protected:
	void set_values();
	void loop_events();
	void draw_all();



public:
	bool mainMenuOpen;
	MainMenu();
	~MainMenu();
	void run_menu(GameWindow* gameWindow);

};

