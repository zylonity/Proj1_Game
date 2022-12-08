#pragma once

#include <SFML\Graphics.hpp>


class MainMenu {
	int pos;
	bool pressed, theselect;


	sf::RenderWindow* window;

	sf::Font* font;
	sf::Texture* image;
	sf::Sprite* background;

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

