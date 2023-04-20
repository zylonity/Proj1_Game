#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include <iostream>
#include <vector>

class Enemy{

	float zHealth;

	float elapsed;

	GameWindow* gameWW;

	float moveSpeed;

	bool justSpawned;


	sf::IntRect zombieRect;

protected:
	void moveTowards();


public:
	Enemy();
	void spawn_zombie(float elapsed, float aniTime, GameWindow* gameWindow, sf::Vector2f playerCoords);
	void draw_zomb(GameWindow* gameWindow);
	sf::Texture tZombie;
	sf::Sprite sZombie;
};

class Game : Enemy{

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

	float wave1TimeToWait, wave1Timer;
	bool wave1Active;
	std::vector<Enemy*> Wave1Zombies;
	sf::FloatRect Wave1Door1, Wave1Door2;

protected:
	GameWindow* gameWin;
	void set_values();
	void loop_events();
	void draw_all();

public:
	Game();
	~Game();
	bool gameOpen;
	void start_game(GameWindow* gameWindow);


};

