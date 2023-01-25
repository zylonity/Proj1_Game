#include "SettingsMenu_Header.h"

typedef SettingsMenu SS;


//set pointers
SS::SettingsMenu() {

	settingsOpen = true;

	font = new sf::Font();
	bgImage = new sf::Texture();
	background = new sf::Sprite();

	pBackButton = new UIButton();

	set_values();
}


//delete pointers
SS::~SettingsMenu() {
	delete font;
	delete bgImage;
	delete background;

	delete pBackButton;

}

void SS::set_values() {

	bgImage->loadFromFile("Resources/Textures/BG.png");
	background->setTexture(*bgImage);
	
	pos = 0;
	clicked = false;
	hovered = false;

	buttonCoords = { {100, 50} };

	pBackButton->create_button(new std::string("Resources/Textures/SharedMenuButtons/BackArrow.png"), 3);


	pBackButton->set_position(buttonCoords[0]);
	

}

void SS::loop_events() {
	sf::Event event;
	while (gameWin.window->pollEvent(event) && settingsOpen)
	{
		if (event.type == sf::Event::Closed) {
			gameWin.window->close();
		}
		
		if (event.type == sf::Event::Resized)
		{
			gameWin.window->setView(gameWin.calculate_viewport(gameWin.window->getSize(), gameWin.designedWinSize));
		}


		gameWin.update_mouse();
		pBackButton->button_detection(gameWin.mouseCoords, event);

		//on letting go of button
		if (pBackButton->validClick) {
			pBackButton->reset_button();
			gameWin.window->clear();
			gameWin.currentScreen = 1;
			settingsOpen = false;
		}

	}

	
	
}

void SS::draw_all() {


	gameWin.window->clear();

	gameWin.window->draw(*background);
	gameWin.window->draw(*pBackButton->sprButton);

	gameWin.window->display();
}

void SS::open_settings(GameWindow* tGameWin) {
	gameWin = *tGameWin;
	settingsOpen = true;
	while (gameWin.window->isOpen() && settingsOpen)
	{
		loop_events();
		draw_all();
	}
}