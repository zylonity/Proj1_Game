#pragma once

#include <SFML\Graphics.hpp>


class MainMenu {
	int pos;
	int buttonCount;
	bool pressed, theselect;


	sf::RenderWindow* window;
	
	sf::Vector2u designedWinSize;
	
	sf::Font* font;
	sf::Texture* bgImage;
	sf::Texture* logoImage;
	sf::Sprite* background;
	sf::Sprite* logo;
	

	std::vector<sf::Texture> texButtons;
	std::vector<sf::Texture> texButtonHighlighted;
	std::vector<sf::Texture> texButtonPressed;

	sf::Sprite* sprButtonPlay;
	sf::Sprite* sprButtonSettings;
	sf::Sprite* sprButtonQuit;
	
	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;

	std::vector<const char*>options;
	std::vector<sf::Vector2f> buttonCoords;
	std::vector<sf::Text> textOptions;
	


protected:
	void set_values();
	sf::Vector2f calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text);
	void loop_events();
	void draw_all();


public:
	MainMenu();
	~MainMenu();
	void run_menu();

};

