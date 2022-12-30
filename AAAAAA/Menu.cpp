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


	for (int i = 0; i < 3; i++) {
		texButtons[i] = new sf::Texture();
		texButtonHighlighted[i] = new sf::Texture();
		texButtonPressed[i] = new sf::Texture();
		
	}
	
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

	for (int i = 0; i < 3; i++) {
		delete texButtons[i];
		delete texButtonHighlighted[i];
		delete texButtonPressed[i];
	}

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


void MM::set_values() {
	
	designedWinSize = (sf::Vector2u (1280, 720));

	window->create(sf::VideoMode(1280, 720), "wOah");
	window->setView(calcView(window->getSize(), designedWinSize));
	
	buttonCount = 3;

	bgImage->loadFromFile("Resources/Textures/BG.png");
	logoImage->loadFromFile("Resources/Textures/TitleScreen.png");

	
	background->setTexture(*bgImage);
	logo->setTexture(*logoImage);
	
	//font->loadFromFile("Resources/Fonts/Blokletters-Balpen.ttf");

	
	sf::Vector2f logoCoords;

	//Get position logo should be in
	logoCoords.x = (designedWinSize.x / 2) - (logoImage->getSize().x / 2);
	logoCoords.y = ((designedWinSize.y / 2) - (logoImage->getSize().y / 2) - 200);

	logo->setPosition(logoCoords);


	options = {"PLAY", "SETTINGS", "QUIT"};
	buttonCoords = { {640, 360}, {640, 420}, {640, 480} };
	//textOptions.resize(3);

	//Play button backing
	texButtons[0]->loadFromFile("Resources/Textures/TitleScreenButtons/1.png");
	texButtons[1]->loadFromFile("Resources/Textures/TitleScreenButtons/2.png");
	texButtons[2]->loadFromFile("Resources/Textures/TitleScreenButtons/3.png");


	//Settings button backing
	texButtonHighlighted[0]->loadFromFile("Resources/Textures/TitleScreenButtons/1_highlighted.png");
	texButtonHighlighted[1]->loadFromFile("Resources/Textures/TitleScreenButtons/2_highlighted.png");
	texButtonHighlighted[2]->loadFromFile("Resources/Textures/TitleScreenButtons/3_highlighted.png");

	
	//Quit button backing
	texButtonPressed[0]->loadFromFile("Resources/Textures/TitleScreenButtons/1_pressed.png");
	texButtonPressed[1]->loadFromFile("Resources/Textures/TitleScreenButtons/2_pressed.png");
	texButtonPressed[2]->loadFromFile("Resources/Textures/TitleScreenButtons/3_pressed.png");
	

	//Set the original button sprites
	sprButtonPlay->setTexture(*texButtons[0]);
	sprButtonSettings->setTexture(*texButtons[1]);
	sprButtonQuit->setTexture(*texButtons[2]);
	
	sprButtonPlay->setPosition(buttonCoords[0]);
	sprButtonSettings->setPosition(buttonCoords[1]);
	sprButtonQuit->setPosition(buttonCoords[2]);
	
	/*for (int i = 0; i < 3; i++) {
		textOptions[i].setFont(*font);
		textOptions[i].setString("*options[i]");
		textOptions[i].setPosition(buttonCoords[i]);
		
		sprButtonPlay->setPosition(buttonCoords[i]);

		
	}*/

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

		//continue if statements

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

	//for (auto t : textOptions) {
	//	window->draw(t);
	//}

	
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