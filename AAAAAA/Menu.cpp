#include "MainMenu_Header.h"
typedef MainMenu MM;


MM::MainMenu() {
	
	window = new sf::RenderWindow();
	
	font = new sf::Font();
	image = new sf::Texture();
	background = new sf::Sprite();

	set_values();
}

MM::~MainMenu() {
	delete window;
	delete font;
	delete image;
	delete background;
}

void MM::set_values() {
	
	window->create(sf::VideoMode(1280, 720), "wOah");
	
	
}

void MM::loop_events() {

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
	
}

void MM::draw_all() {
	window->clear();
	window->display();
}

void MM::run_menu() {
	while (window->isOpen())
	{
		loop_events();
		draw_all();
	}
}