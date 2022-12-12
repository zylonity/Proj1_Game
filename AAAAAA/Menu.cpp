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
	
	bgImage->loadFromFile("Resources/Textures/BG.png");
	logoImage->loadFromFile("Resources/Textures/TitleScreen.png");

	
	background->setTexture(*bgImage);
	logo->setTexture(*logoImage);
	
	sf::Vector2f logoCoords;

	//Get position logo should be in
	logoCoords.x = (designedWinSize.x / 2) - (logoImage->getSize().x / 2);
	logoCoords.y = ((designedWinSize.y / 2) - (logoImage->getSize().y / 2) - 200);

	logo->setPosition(logoCoords);
	
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