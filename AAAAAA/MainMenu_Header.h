#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow_Header.h"

class MainMenu {
	int pos;
	int buttonCount;
	bool clicked, hovered;

	GameWindow gameWin;
	
	sf::Font* font;
	sf::Texture* bgImage;
	sf::Texture* logoImage;
	sf::Sprite* background;
	sf::Sprite* logo;
	

	std::vector<sf::Texture> texButtons;
	std::vector<sf::Texture> texButtonHighlighted;
	std::vector<sf::Texture> texButtonPressed;

	sf::Sprite* sprButtonPlay;
	sf::Sprite* sprButtonSettings;
	sf::Sprite* sprButtonQuit;
	
	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;

	std::vector<const char*>options;
	std::vector<sf::Vector2f> buttonCoords;
	std::vector<sf::Text> textOptions;
	


protected:
	void set_values();
	void loop_events();
	void draw_all();



public:
	MainMenu();
	~MainMenu();
	void run_menu(GameWindow* gameWindow);

};

