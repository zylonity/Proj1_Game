#pragma once

#include <SFML\Graphics.hpp>
#include "UI_Elements\UI_Button.h"


class GameWindow {


	

public:
	bool justOpened;
	int currentScreen;
	sf::RenderWindow* window;
	sf::Vector2u designedWinSize;
	sf::View calculate_viewport(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize);
	sf::Vector2f calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text);
	GameWindow();
	~GameWindow();
	void run_window();

	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;
	void update_mouse();

};

