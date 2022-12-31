#include "MainMenu_Header.h"
#include <assert.h>

typedef MainMenu MM;


//assign the values to the pointers
MM::MainMenu() {
	
	window = new sf::RenderWindow();

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
	delete window;
	delete font;

	delete bgImage;
	delete logoImage;

	delete background;
	delete logo;


	delete sprButtonPlay;
	delete sprButtonSettings;
	delete sprButtonQuit;
	
}


//Keep viewport scaling correct
sf::View calcView(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize)
{
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

sf::Vector2f MM::calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text) {
	
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

}

void MM::set_values() {
	
	designedWinSize = (sf::Vector2u (1280, 720));

	window->create(sf::VideoMode(1280, 720), "wOah");
	window->setView(calcView(window->getSize(), designedWinSize));
	
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
	logoCoords.x = (designedWinSize.x / 2) - (logoImage->getSize().x / 2);
	logoCoords.y = ((designedWinSize.y / 2) - (logoImage->getSize().y / 2) - 200);

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
	sprButtonPlay->setPosition(*new sf::Vector2f(buttonCoords[0] - calculate_obj_offset(0, &texButtonPressed[0], 0))); //gets the coordinates and adjusts for button size
	sprButtonSettings->setPosition(*new sf::Vector2f(buttonCoords[1] - calculate_obj_offset(0, &texButtonPressed[1], 0)));
	sprButtonQuit->setPosition(*new sf::Vector2f(buttonCoords[2] - calculate_obj_offset(0, &texButtonPressed[2], 0)));
	
	
	for (int i = 0; i < textOptions.size(); i++) {
		textOptions[i].setFont(*font);
		textOptions[i].setString(options[i]);
		textOptions[i].setCharacterSize(20);
		textOptions[i].setFillColor(sf::Color::Black);
		textOptions[i].setPosition(*new sf::Vector2f(buttonCoords[i] - calculate_obj_offset(0, 0, &textOptions[i])));

		
	}

}




//deals with everything that needs to be looped
//checking if the program is closed, checking if the mouse is pressed, etc
void MM::loop_events() {

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) 
		{
			window->close();
		}

		if (event.type == sf::Event::Resized) 
		{
			window->setView(calcView(window->getSize(), designedWinSize));
		}

		pos_mouse = sf::Mouse::getPosition(*window);
		mouseCoords = window->mapPixelToCoords(pos_mouse);

		sf::FloatRect playRect = sprButtonPlay->getGlobalBounds();
		sf::FloatRect settingsRect = sprButtonSettings->getGlobalBounds();
		sf::FloatRect quitRect = sprButtonQuit->getGlobalBounds();

		if (playRect.contains(mouseCoords)) {
			sprButtonPlay->setTexture(texButtonHighlighted[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = true;
			pos = 0;
		}
		else if (settingsRect.contains(mouseCoords)) {
			sprButtonSettings->setTexture(texButtonHighlighted[1]);
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = true;
			pos = 1;
		}
		else if (quitRect.contains(mouseCoords)) {
			sprButtonQuit->setTexture(texButtonHighlighted[2]);
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			hovered = true;
			pos = 2;
		}
		else {
			sprButtonPlay->setTexture(texButtons[0]);
			sprButtonSettings->setTexture(texButtons[1]);
			sprButtonQuit->setTexture(texButtons[2]);
			hovered = false;
		}
		
		//continue if statements

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && hovered) {
			if (sprButtonPlay->getTexture() == &texButtonHighlighted[0]) {
				sprButtonPlay->setTexture(texButtonPressed[0]);
				clicked = true;
			}
			else if (sprButtonSettings->getTexture() == &texButtonHighlighted[1]) {
				sprButtonSettings->setTexture(texButtonPressed[1]);
				clicked = true;
			}
			else if (sprButtonQuit->getTexture() == &texButtonHighlighted[2]) {
				sprButtonQuit->setTexture(texButtonPressed[2]);
				window->close();
				clicked = true;
			}
		}

	}
	
}


//just deals with drawing everything onto the screen
void MM::draw_all() {



	window->clear();

	window->draw(*background);
	window->draw(*logo);

	window->draw(*sprButtonPlay);
	window->draw(*sprButtonSettings);
	window->draw(*sprButtonQuit);

	for (auto t : textOptions) {
		window->draw(t);
	}

	
	window->display();
}


//what is needed to run the menu
void MM::run_menu() {
	while (window->isOpen())
	{
		loop_events();
		draw_all();
	}
}