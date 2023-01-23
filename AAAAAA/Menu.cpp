#include "MainMenu_Header.h"
#include "GameWindow_Header.h"
#include "SettingsMenu_Header.h"

#include <assert.h>

typedef MainMenu MM;


//assign the values to the pointers
MM::MainMenu() {
	mainMenuOpen = true;
	font = new sf::Font();
	bgImage = new sf::Texture();
	logoImage = new sf::Texture();
	background = new sf::Sprite();
	logo = new sf::Sprite();
	
	sprButtonPlay = new sf::Sprite();
	sprButtonSettings = new sf::Sprite();
	sprButtonQuit = new sf::Sprite();
	
	
	set_values();
}


//delete all the pointers from memory
MM::~MainMenu() {
	delete font;

	delete bgImage;
	delete logoImage;

	delete background;
	delete logo;


	delete sprButtonPlay;
	delete sprButtonSettings;
	delete sprButtonQuit;
	
}

void MM::set_values() {
	
	buttonCount = 3;

	bgImage->loadFromFile("Resources/Textures/BG.png");
	logoImage->loadFromFile("Resources/Textures/TitleScreen.png");

	
	background->setTexture(*bgImage);
	logo->setTexture(*logoImage);
	
	font->loadFromFile("Resources/Fonts/Blokletters-Balpen.ttf");

	pos = 0;
	clicked = false;
	hovered = false;
	
	mouseCoords = {0, 0};
	pos_mouse = { 0, 0 };
	
	sf::Vector2f logoCoords;

	//Get position logo should be in
	logoCoords.x = (gameWin.designedWinSize.x / 2) - (logoImage->getSize().x / 2);
	logoCoords.y = ((gameWin.designedWinSize.y / 2) - (logoImage->getSize().y / 2) - 200);

	logo->setPosition(logoCoords);


	options = {"PLAY", "SETTINGS", "QUIT"};
	buttonCoords = { {640, 340}, {640, 460}, {640, 580} };
	
	textOptions.resize(3);


	
	texButtons.resize(3);
	texButtonHighlighted.resize(3);
	texButtonPressed.resize(3);

	//Load original textures
	texButtons[0].loadFromFile("Resources/Textures/TitleScreenButtons/1.png");
	texButtons[1].loadFromFile("Resources/Textures/TitleScreenButtons/2.png");
	texButtons[2].loadFromFile("Resources/Textures/TitleScreenButtons/3.png");


	//Load highlighted textures
	texButtonHighlighted[0].loadFromFile("Resources/Textures/TitleScreenButtons/1_highlighted.png");
	texButtonHighlighted[1].loadFromFile("Resources/Textures/TitleScreenButtons/2_highlighted.png");
	texButtonHighlighted[2].loadFromFile("Resources/Textures/TitleScreenButtons/3_highlighted.png");


	//Load pressed textures
	texButtonPressed[0].loadFromFile("Resources/Textures/TitleScreenButtons/1_pressed.png");
	texButtonPressed[1].loadFromFile("Resources/Textures/TitleScreenButtons/2_pressed.png");
	texButtonPressed[2].loadFromFile("Resources/Textures/TitleScreenButtons/3_pressed.png");
	
	
	//Set the original button sprites
	sprButtonPlay->setTexture(texButtons[0]);
	sprButtonSettings->setTexture(texButtons[1]);
	sprButtonQuit->setTexture(texButtons[2]);
	

	//Set the button positions
	sprButtonPlay->setPosition(*new sf::Vector2f(buttonCoords[0] - gameWin.calculate_obj_offset(0, &texButtons[0], 0))); //gets the coordinates and adjusts for button size
	sprButtonSettings->setPosition(*new sf::Vector2f(buttonCoords[1] - gameWin.calculate_obj_offset(0, &texButtons[1], 0)));
	sprButtonQuit->setPosition(*new sf::Vector2f(buttonCoords[2] - gameWin.calculate_obj_offset(0, &texButtons[2], 0)));
	
	
	for (int i = 0; i < textOptions.size(); i++) {
		textOptions[i].setFont(*font);
		textOptions[i].setString(options[i]);
		textOptions[i].setCharacterSize(20);
		textOptions[i].setFillColor(sf::Color::Black);
		textOptions[i].setPosition(*new sf::Vector2f(buttonCoords[i] - gameWin.calculate_obj_offset(0, 0, &textOptions[i])));

		
	}

}




//deals with everything that needs to be looped
//checking if the program is closed, checking if the mouse is pressed, etc
void MM::loop_events() {

	sf::Event event;
	while (gameWin.window->pollEvent(event) && mainMenuOpen)
	{
		if (event.type == sf::Event::Closed) 
		{
			gameWin.window->close();
		}

		if (event.type == sf::Event::Resized) 
		{
			gameWin.window->setView(gameWin.calculate_viewport(gameWin.window->getSize(), gameWin.designedWinSize));
		}

		pos_mouse = sf::Mouse::getPosition(*gameWin.window);
		mouseCoords = gameWin.window->mapPixelToCoords(pos_mouse);

		sf::FloatRect playRect = sprButtonPlay->getGlobalBounds();
		sf::FloatRect settingsRect = sprButtonSettings->getGlobalBounds();
		sf::FloatRect quitRect = sprButtonQuit->getGlobalBounds();

		//Deal with play button highlights
		if (playRect.contains(mouseCoords)) {
			sprButtonPlay->setTexture(texButtonHighlighted[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sprButtonPlay->setTexture(texButtonPressed[0]);
				clicked = true;
			}
			
			pos = 1;
		}
		//deal with settings button highlights
		else if (settingsRect.contains(mouseCoords)) {
			sprButtonSettings->setTexture(texButtonHighlighted[1]);
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = true;
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sprButtonSettings->setTexture(texButtonPressed[1]);
				clicked = true;
			}
			
			pos = 2;
		}
		//deal with quit button highlights
		else if (quitRect.contains(mouseCoords)) {
			sprButtonQuit->setTexture(texButtonHighlighted[2]);
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			hovered = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sprButtonQuit->setTexture(texButtonPressed[2]);
				clicked = true;
			}
			
			pos = 3;
		}
		else {
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = false;
			clicked = false;
		}
		
		
		//On letting go of button

		if (event.type == sf::Event::MouseButtonReleased) {
			
			if (clicked) {
				//Play
				if (pos == 1) {
					
				}
				//Settings
				else if (pos == 2) {
					gameWin.currentScreen = 2;
					gameWin.window->clear();
					mainMenuOpen = false;

					
				}
				//Quit
				else if (pos == 3) {
					gameWin.window->close();
				}
			}
			
		}
		
		
		

	}
	
}


//just deals with drawing everything onto the screen
void MM::draw_all() {



	gameWin.window->clear();

	gameWin.window->draw(*background);
	gameWin.window->draw(*logo);

	gameWin.window->draw(*sprButtonPlay);
	gameWin.window->draw(*sprButtonSettings);
	gameWin.window->draw(*sprButtonQuit);

	for (auto t : textOptions) {
		gameWin.window->draw(t);
	}

	
	gameWin.window->display();
}


//what is needed to run the menu
void MM::run_menu(GameWindow* tGameWin) {
	gameWin = *tGameWin;
	mainMenuOpen = true;
	while (gameWin.window->isOpen() && mainMenuOpen)
	{
		loop_events();
		draw_all();
	}
}