#pragma once

#include <SFML\Graphics.hpp>


class MainMenu {
	int pos;
	bool pressed, theselect;


	sf::RenderWindow* window;
	
	sf::Vector2u designedWinSize;
	
	sf::Font* font;
	sf::Texture* bgImage;
	sf::Texture* logoImage;
	sf::Sprite* background;
	sf::Sprite* logo;

	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;


protected:
	void set_values();
	void loop_events();
	void draw_all();


public:
	MainMenu();
	~MainMenu();
	void run_menu();

};

