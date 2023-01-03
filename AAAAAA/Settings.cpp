#include "SettingsMenu_Header.h"

typedef SettingsMenu SS;


//set pointers
SS::SettingsMenu() {
	settingsWindow = new sf::RenderWindow();

	font = new sf::Font();
	image = new sf::Texture();
	background = new sf::Sprite();

	set_values();
}


//delete pointers
SS::~SettingsMenu() {
	delete settingsWindow;
	delete font;
	delete image;
	delete background;
}

void SS::set_values() {
	settingsWindow->create(sf::VideoMode(1280, 720), "wOah");
}

void SS::loop_events() {
	sf::Event event;
	while (settingsWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			settingsWindow->close();
	}
}

void SS::draw_all() {
	settingsWindow->clear();
	settingsWindow->display();
}

void SS::open_settings() {
	while (settingsWindow->isOpen())
	{
		loop_events();
		draw_all();
	}
}