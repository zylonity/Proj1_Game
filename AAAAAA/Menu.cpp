#include "MainMenu_Header.h"

#include <assert.h>

typedef MainMenu MM;


//assign the values to the pointers
MM::MainMenu() {
	mainMenuOpen = true;
	

}


//delete all the pointers from memory
MM::~MainMenu() {

	
}

void MM::set_values() {
	
	buttonCount = 3;

	bgImage.loadFromFile("Resources/Textures/BG.png");
	logoImage.loadFromFile("Resources/Textures/TitleScreen.png");

	
	background.setTexture(bgImage);
	logo.setTexture(logoImage);
	
	font.loadFromFile("Resources/Fonts/Blokletters-Balpen.ttf");

	pos = 0;
	clicked = false;
	hovered = false;
	
	
	sf::Vector2f logoCoords;

	//Get position logo should be in
	logoCoords.x = (gameWin->designedWinSize.x / 2) - (logoImage.getSize().x / 2);
	logoCoords.y = ((gameWin->designedWinSize.y / 2) - (logoImage.getSize().y / 2) - 200);

	logo.setPosition(logoCoords);


	options = {"PLAY", "SETTINGS", "QUIT"};
	buttonCoords = { {640, 340}, {640, 460}, {640, 580} };
	
	textOptions.resize(3);

	playButton.create_button(("Resources/Textures/TitleScreenButtons/play_button.png"), 3);
	settingsButton.create_button(("Resources/Textures/TitleScreenButtons/settings_button.png"), 3);
	quitButton.create_button(("Resources/Textures/TitleScreenButtons/quit_button.png"), 3);

	playButton.set_position(buttonCoords[0]);
	settingsButton.set_position(buttonCoords[1]);
	quitButton.set_position(buttonCoords[2]);
	
	
	
	for (int i = 0; i < textOptions.size(); i++) {
		textOptions[i].setFont(font);
		textOptions[i].setString(options[i]);
		textOptions[i].setCharacterSize(20);
		textOptions[i].setFillColor(sf::Color::Black);
		textOptions[i].setPosition(*new sf::Vector2f(buttonCoords[i] - gameWin->calculate_obj_offset(0, 0, &textOptions[i])));

		
	}

}




//deals with everything that needs to be looped
//checking if the program is closed, checking if the mouse is pressed, etc
void MM::loop_events() {

	sf::Event event;
	while (gameWin->window.pollEvent(event) && mainMenuOpen)
	{
		if (event.type == sf::Event::Closed) 
		{
			gameWin->window.close();
		}

		if (event.type == sf::Event::Resized) 
		{
			gameWin->window.setView(gameWin->calculate_viewport(gameWin->window.getSize(), gameWin->designedWinSize));
		}

		gameWin->update_mouse();

		playButton.button_detection(gameWin->mouseCoords, event); 
		settingsButton.button_detection(gameWin->mouseCoords, event);
		quitButton.button_detection(gameWin->mouseCoords, event);
		
		if (playButton.validClick) {
			playButton.reset_button();

		}

		if (settingsButton.validClick) {
			settingsButton.reset_button();
			gameWin->currentScreen = 2;
			gameWin->window.clear();
			mainMenuOpen = false;

		}

		if (quitButton.validClick) {
			quitButton.reset_button();
			gameWin->window.close();

		}
		
		
		
		

	}
	
}


//just deals with drawing everything onto the screen
void MM::draw_all() {



	gameWin->window.clear();

	gameWin->window.draw(background);
	gameWin->window.draw(logo);

	gameWin->window.draw(playButton.sprButton);
	gameWin->window.draw(settingsButton.sprButton);
	gameWin->window.draw(quitButton.sprButton);

	for (auto t : textOptions) {
		gameWin->window.draw(t);
	}

	
	gameWin->window.display();
}


//what is needed to run the menu
void MM::run_menu(GameWindow* tGameWin) {
	gameWin = tGameWin;
	mainMenuOpen = true;
	set_values();
	while (gameWin->window.isOpen() && mainMenuOpen)
	{
		loop_events();
		draw_all();
	}

}