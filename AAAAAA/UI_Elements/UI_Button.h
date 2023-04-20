#pragma once

#include <SFML\Graphics.hpp>

namespace UI {
	class Button {

		sf::IntRect rectButton;
		sf::FloatRect buttonBounds;
		sf::Texture texButton;

		bool clickDown;
		bool hovering;

		int spriteTabs;
		int xWidth;


	public:
		sf::Sprite sprButton;
		bool validClick;
		void create_button(const char *fileLocation, int tempTabs);
		void button_detection(sf::Vector2f mouseCoords, sf::Event vent);
		void set_position(sf::Vector2f pos);
		void sprite_to_show(int sprNum);
		void reset_button();
		Button();

	};
}

