#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"

typedef SettingsMenu SS;


//set pointers
SS::SettingsMenu() {

	settingsOpen = true;

	font = new sf::Font();
	bgImage = new sf::Texture();
	background = new sf::Sprite();

	texBackArrow = new sf::Texture();
	sprBackArrow = new sf::Sprite();


	set_values();
}


//delete pointers
SS::~SettingsMenu() {
	delete font;
	delete bgImage;
	delete background;

	delete texBackArrow;
	delete sprBackArrow;
}

void SS::set_values() {

	bgImage->loadFromFile("Resources/Textures/BG.png");
	background->setTexture(*bgImage);
	
	pos = 0;
	clicked = false;
	hovered = false;

	mouseCoords = { 0, 0 };
	pos_mouse = { 0, 0 };

	buttonCoords = { {100, 50} };



	rectBackArrow = new sf::IntRect(0, 0, 91, 59);
	texBackArrow->loadFromFile("Resources/Textures/SharedMenuButtons/BackArrow.png");
	sprBackArrow->setTexture(*texBackArrow);
	sprBackArrow->setTextureRect(*rectBackArrow);
	
	//Set the position of the sprite
	sprBackArrow->setPosition(buttonCoords[0]);
	

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

		//grabs mouse pos
		pos_mouse = sf::Mouse::getPosition(*gameWin.window);
		mouseCoords = gameWin.window->mapPixelToCoords(pos_mouse);

		sf::FloatRect backRect = sprBackArrow->getGlobalBounds();

		//deal with play button highlights
		if (backRect.contains(mouseCoords)) {
			rectBackArrow->left = rectBackArrow->width;
			sprBackArrow->setTextureRect(*rectBackArrow);
			//don't forget to reset whatever other buttons you add
			hovered = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				rectBackArrow->left = rectBackArrow->width*2;
				sprBackArrow->setTextureRect(*rectBackArrow);
				clicked = true;
			}

			pos = 1;

		}
		else {
			rectBackArrow->left = 0;
			sprBackArrow->setTextureRect(*rectBackArrow);
			hovered = false;
			clicked = false;

		}

		//on letting go of button
		if (event.type == sf::Event::MouseButtonReleased) {
			if (clicked) {
				if (pos == 1) {

					gameWin.window->clear();
					gameWin.currentScreen = 1;
					settingsOpen = false;



				}
			}
		}

	}

	
	
}

void SS::draw_all() {


	gameWin.window->clear();

	gameWin.window->draw(*background);
	gameWin.window->draw(*sprBackArrow);

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