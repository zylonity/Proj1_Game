#pragma once

#include <SFML\Graphics.hpp>

class SettingsMenu {
	
	sf::RenderWindow* settingsWindow;

	sf::Sprite* background;


protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	Settings();
	~Settings();
	void open_settings();
	
	
};