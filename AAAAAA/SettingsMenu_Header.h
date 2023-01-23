#pragma once

#include <SFML\Graphics.hpp>

class SettingsMenu {
	
	sf::RenderWindow* settingsWindow;

	sf::Font* font;
	sf::Texture* bgImage;
	sf::Sprite* background;



protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	SettingsMenu();
	~SettingsMenu();
	void open_settings(sf::RenderWindow* ssWindow);
	
	
};