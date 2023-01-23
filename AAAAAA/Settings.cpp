#include "MainMenu_Header.h"
#include "SettingsMenu_Header.h"

typedef SettingsMenu SS;


//set pointers
SS::SettingsMenu() {

	font = new sf::Font();
	bgImage = new sf::Texture();
	background = new sf::Sprite();

	sprButtonBack = new sf::Sprite();

	set_values();
}


//delete pointers
SS::~SettingsMenu() {
	delete font;
	delete bgImage;
	delete background;
	delete sprButtonBack;
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

	texButtons.resize(1);
	texButtonHighlighted.resize(1);
	texButtonPressed.resize(1);

	//Load og texture
	texButtons[0].loadFromFile("Resources/Textures/SharedMenuButtons/Back1.png");

	//load highlighted texture
	texButtonHighlighted[0].loadFromFile("Resources/Textures/SharedMenuButtons/Back2.png");

	//load pressed texture
	texButtonPressed[0].loadFromFile("Resources/Textures/SharedMenuButtons/Back3.png");


	//Set the first texture onto the sprite
	sprButtonBack->setTexture(texButtons[0]);
	
	//Set the position of the sprite
	sprButtonBack->setPosition(*new sf::Vector2f(buttonCoords[0] - gameWin.calculate_obj_offset(0, &texButtons[0], 0)));
	

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
	
	//grabs mouse pos
	pos_mouse = sf::Mouse::getPosition(*gameWin.window);
	mouseCoords = gameWin.window->mapPixelToCoords(pos_mouse);

	sf::FloatRect backRect = sprButtonBack->getGlobalBounds();

	//deal with play button highlights
	if (backRect.contains(mouseCoords)) {
		sprButtonBack->setTexture(texButtonHighlighted[0]);
		//don't forget to reset whatever other buttons you add
		hovered = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sprButtonBack->setTexture(texButtonPressed[0]);
			clicked = true;
		}
		
		pos = 1;
		
	}
	else {
		sprButtonBack->setTexture(texButtons[0]);
		hovered = false;
		clicked = false;

	}

	//on letting go of button
	if (event.type == sf::Event::MouseButtonReleased) {
		if (clicked) {
			if (pos == 1) {
				
				gameWin.currentScreen = 1;
				gameWin.window->clear();
				
				
			}
		}
	}
	
}

void SS::draw_all() {


	gameWin.window->clear();

	gameWin.window->draw(*background);
	gameWin.window->draw(*sprButtonBack);

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