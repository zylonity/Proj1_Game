#include "GameWindow.h"
#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"

GameWindow::GameWindow() {
	//window = new sf::RenderWindow();
	designedWinSize = sf::Vector2u(1280, 720);

	mouseCoords = { 0, 0 };
	pos_mouse = { 0, 0 };

}

GameWindow::~GameWindow() {
	//delete window;
}


//calculates the size of the viewport
sf::View GameWindow::calculate_viewport(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize) {
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

	float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
	float screenheight = windowsize.y / static_cast<float>(designedsize.y);

	if (screenwidth > screenheight)
	{
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if (screenwidth < screenheight)
	{
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}

	sf::View view(sf::FloatRect(0, 0, designedsize.x, designedsize.y));
	view.setViewport(viewport);

	return view;
}

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

void GameWindow::run_window() {
	MainMenu menu = MainMenu::MainMenu();
	SettingsMenu settings = SettingsMenu::SettingsMenu();

	window.create(sf::VideoMode(1280, 720), "wOah");

	currentScreen = 1;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		//manage which menu goes where depending on the ID
		switch (currentScreen) {
		case 1:
			menu.run_menu(this);
		case 2:
			settings.open_settings(this);
		}


		window.clear();
		window.display();
	}

}