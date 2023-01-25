#pragma once

#include <SFML\Graphics.hpp>


class GameWindow {


	

public:
	bool justOpened;
	int currentScreen;
	sf::RenderWindow* window;
	sf::Vector2u designedWinSize;
	sf::View calculate_viewport(const sf::Vector2u& windowsize, const sf::Vector2u& designedsize);
	sf::Vector2f calculate_obj_offset(sf::Sprite* sprite, sf::Texture* texture, sf::Text* text);
	GameWindow();
	~GameWindow();
	void run_window();

	sf::Vector2i pos_mouse;
	sf::Vector2f mouseCoords;
	void update_mouse();

};

class UIButton {

	sf::IntRect* rectButton;
	sf::FloatRect* buttonBounds;
	sf::Texture* texButton;

	bool clickDown;
	bool hovering;

	int* spriteTabs;
	int* xWidth;


public:
	sf::Sprite* sprButton;
	bool validClick;
	void create_button(std::string* strButtonLocation, int tempTabs);
	void button_detection(sf::Vector2f mouseCoords, sf::Event vent);
	void set_position(sf::Vector2f pos);
	void sprite_to_show(int sprNum);
	void reset_button();
	UIButton();
	~UIButton();

};