#include "GameWindow_header.h"

UIButton::UIButton() {
	
	texButton = new sf::Texture();
	sprButton = new sf::Sprite();

	clickDown = false;
	validClick = false;
}

UIButton::~UIButton() {
	delete rectButton;
	delete texButton;
	delete sprButton;
	delete buttonBounds;

	delete spriteTabs;
	delete xWidth;

}

void UIButton::create_button(std::string* tempLoc, int tabs) {

	spriteTabs = new int(tabs);


	texButton->loadFromFile(*tempLoc);
	sprButton->setTexture(*texButton);

	xWidth = new int(texButton->getSize().x / *spriteTabs);

	rectButton = new sf::IntRect(0, 0, *xWidth, texButton->getSize().y);

	sprButton->setTextureRect(*rectButton);



}

void UIButton::button_detection(sf::Vector2f mouseCoords, sf::Event vent) {

	buttonBounds = new sf::FloatRect(sprButton->getGlobalBounds());

	if (buttonBounds->contains(mouseCoords)) {
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

void UIButton::set_position(sf::Vector2f tempPos) {
	sprButton->setPosition(sf::Vector2f((tempPos.x - rectButton->width/2), (tempPos.y - rectButton->height /2)));
}

void UIButton::sprite_to_show(int sprNum) {

	rectButton->left = *xWidth * sprNum;
	sprButton->setTextureRect(*rectButton);
}


void UIButton::reset_button() {
	clickDown = false;
	validClick = false;
	sprButton->setTextureRect(sf::IntRect(0, 0, *xWidth, texButton->getSize().y));
}
