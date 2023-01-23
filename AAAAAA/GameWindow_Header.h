#pragma once

#include <SFML\Graphics.hpp>


class GameWindow {





protected:
	//void set_values();
	//void loop_events();
	//void draw_all();


public:
	int currentScreen;
	sf::RenderWindow* window;
	sf::Vector2u designedWinSize;
	sf::View calculate_viewport(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize);
	GameWindow();
	~GameWindow();
	void run_window();

};

