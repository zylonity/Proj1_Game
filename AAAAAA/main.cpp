#include "GameWindow_Header.h"
#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"
#include <SFML\Graphics.hpp>

GameWindow::GameWindow() {
	window = new sf::RenderWindow();
	designedWinSize = sf::Vector2u(1280, 720);
	currentScreen = 1;
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


int main() {

	GameWindow* gameWindow = new GameWindow();
	MainMenu* menu = new MainMenu();
	SettingsMenu* settings = new SettingsMenu();
	
	gameWindow->window->create(sf::VideoMode(1280, 720), "wOah");

	
	while (gameWindow->window->isOpen()) {
		sf::Event event;
		while (gameWindow->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow->window->close();
			}
			
		}

		switch (gameWindow->currentScreen) {
		case 1:
			menu->run_menu(gameWindow);
		case 2:
			settings->open_settings(gameWindow);
		}

		
		gameWindow->window->clear();
		gameWindow->window->display();
	}



	////Once run_menu's done continue here
	//delete menu;
	//menu = nullptr;
	

	return 1;
}
