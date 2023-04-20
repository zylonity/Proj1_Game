#include "UI_Button.h"


//UI Namespace, handles my GUI stuff for menus
namespace UI {
	Button::Button() {
		clickDown = false;
		hovering = false;
		validClick = false;
	}

	void Button::create_button(const char* fileLocation, int tabs) {

		spriteTabs = tabs;


		texButton.loadFromFile(fileLocation);
		sprButton.setTexture(texButton);

		xWidth = texButton.getSize().x / tabs;

		rectButton = sf::IntRect(0, 0, xWidth, texButton.getSize().y);

		sprButton.setTextureRect(rectButton);



	}

	void Button::button_detection(sf::Vector2f mouseCoords, sf::Event vent) {

		buttonBounds = sf::FloatRect(sprButton.getGlobalBounds());

		if (buttonBounds.contains(mouseCoords)) {
			sprite_to_show(1);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sprite_to_show(2);
				clickDown = true;
			}
		}
		else {
			reset_button();
		}

		//on letting go of button
		if (vent.type == sf::Event::MouseButtonReleased && clickDown) {
			validClick = true;
		}

	}

	void Button::set_position(sf::Vector2f tempPos) {
		sprButton.setPosition(sf::Vector2f((tempPos.x - rectButton.width / 2), (tempPos.y - rectButton.height / 2)));
	}

	void Button::sprite_to_show(int sprNum) {

		rectButton.left = xWidth * sprNum;
		sprButton.setTextureRect(rectButton);
	}


	void Button::reset_button() {
		clickDown = false;
		validClick = false;
		sprButton.setTextureRect(sf::IntRect(0, 0, xWidth, texButton.getSize().y));
	}

	
}



