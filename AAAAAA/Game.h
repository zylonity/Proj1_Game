#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Game {
	
	GameWindow* gameWin;

	sf::Font font;

	sf::View view;

	sf::Texture bgImage_1, bgImage_2;
	sf::Sprite backgroundP1, backgroundP2;


protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	Game();
	~Game();
	bool gameOpen;
	void start_game(GameWindow* gameWindow);


};