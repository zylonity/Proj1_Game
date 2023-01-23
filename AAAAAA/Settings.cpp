#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"

typedef SettingsMenu SS;


//set pointers
SS::SettingsMenu() {

	font = new sf::Font();
	bgImage = new sf::Texture();
	background = new sf::Sprite();

	set_values();
}


//delete pointers
SS::~SettingsMenu() {
	delete font;
	delete bgImage;
	delete background;
}

void SS::set_values() {

	bgImage->loadFromFile("Resources/Textures/BG.png");
	background->setTexture(*bgImage);

}

void SS::loop_events() {
	sf::Event event;
	while (gameWin.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gameWin.window->close();
	}

	if (event.type == sf::Event::Resized)
	{
		gameWin.window->setView(gameWin.calculate_viewport(gameWin.window->getSize(), gameWin.designedWinSize));
	}
	
}

void SS::draw_all() {


	gameWin.window->clear();

	gameWin.window->draw(*background);

	gameWin.window->display();
}

void SS::open_settings(GameWindow* tGameWin) {
	gameWin = *tGameWin;
	while (gameWin.window->isOpen())
	{
		loop_events();
		draw_all();
	}
}