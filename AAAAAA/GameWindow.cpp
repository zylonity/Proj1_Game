#include "GameWindow.h"
#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"
#include "Game.h"

GameWindow::GameWindow() {
	//window = new sf::RenderWindow();
	designedWinSize = sf::Vector2u(1920, 1080);

	mouseCoords = { 0, 0 };
	pos_mouse = { 0, 0 };

	defBgImage.loadFromFile("Resources/Textures/BG.png");

}

GameWindow::~GameWindow() {
	//delete window;
}


//UNUSED, but it works to help me rescale the window, I ended up ditching it because of time

//calculates the size of the viewport
//sf::View GameWindow::calculate_viewport(sf::FloatRect viewport) {
//	sf::Vector2u windowsize = window.getSize();
//
//	float screenwidth = windowsize.x / static_cast<float>(designedWinSize.x);
//	float screenheight = windowsize.y / static_cast<float>(designedWinSize.y);
//
//	if (screenwidth > screenheight)
//	{
//		viewport.width = screenheight / screenwidth;
//		viewport.left = ((1.f - viewport.width) / 2.f);
//	}
//	else if (screenwidth < screenheight)
//	{
//		viewport.height = screenwidth / screenheight;
//		viewport.top = (1.f - viewport.height) / 2.f;
//	}
//
//	sf::View view(sf::FloatRect(0, 0, designedWinSize.x, designedWinSize.y));
//	view.setViewport(viewport);
//
//	return view;
//}



sf::Vector2f GameWindow::calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text) {

	if (sprite != 0) {
		sf::Vector2f offset = sf::Vector2f(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
		return offset;
	}
	else if (texture != 0) {
		sf::Vector2f offset = sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2);
		return offset;
	}
	else if (text != 0) {
		sf::Vector2f offset = sf::Vector2f(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
		return offset;
	}
	else {
		return sf::Vector2f(0, 0);
	}

	return sf::Vector2f(0, 0);
}

void GameWindow::update_mouse() {
	pos_mouse = sf::Mouse::getPosition(window);
	mouseCoords = window.mapPixelToCoords(pos_mouse);
}


//Handles main menu stuff and window switching.
//Window is accesed through a pointer at any given time, as I can't recreate them every time and it saves time
void GameWindow::run_window() {

	//1<<2 means it cant resize or maxsimize.
	window.create(sf::VideoMode(1920, 1080), "wOah", 1<<2);
	window.setSize(sf::Vector2u(1280, 720));

	//window.setFramerateLimit(60);

	currentScreen = 1;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		if (currentScreen == 1) {
			MainMenu menu = MainMenu::MainMenu();
			menu.run_menu(this);
		}
		else if (currentScreen == 2) {
			SettingsMenu settings = SettingsMenu::SettingsMenu();
			settings.open_settings(this);
		}
		else if (currentScreen == 3) {
			Game game = Game::Game();
			game.start_game(this);
		}



		window.clear();
		window.display();
	}

}
