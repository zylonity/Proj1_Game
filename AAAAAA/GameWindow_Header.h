#pragma once

#include <SFML\Graphics.hpp>


class GameWindow {


	

public:
	int currentScreen;
	sf::RenderWindow* window;
	sf::Vector2u designedWinSize;
	sf::View calculate_viewport(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize);
	sf::Vector2f calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text);
	GameWindow();
	~GameWindow();
	void run_window();
	void switchToScreen(int id);

};

