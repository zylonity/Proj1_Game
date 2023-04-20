#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Game {
	
	GameWindow* gameWin;

	sf::Font font;

	sf::View view;

	sf::Texture bgImage_1, bgImage_2;
	sf::Sprite backgroundP1, backgroundP2;

	sf::Texture tPlayerIdle;
	sf::Sprite sPlayer;
	sf::IntRect playerRect;
	int playerHealth;


	float playerSpeed;
	float playerJumpHeight;
	bool reachedJumpHeight;
	bool jumped;

	float cameraSpeed;

	float animSpeed;

	sf::Clock clock;
	float timeSinceLastFrame;
	float elapsedTime;


	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	float accelerationSpeed;
	float gravity;


	sf::FloatRect floorTest[13];
	sf::RectangleShape floorDisplay[13];


protected:
	void set_values();
	void loop_events();
	void draw_all();

public:
	Game();
	~Game();
	bool gameOpen;
	void start_game(GameWindow* gameWindow);


};