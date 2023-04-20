#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include <iostream>
#include <vector>


//Enemy class for the zombies
class Enemy{



	float elapsed;

	float moveSpeed;

	bool justSpawned;

	float damageCooldown;
	float damageCooldownTimer;

	float damageAnimTime;



public:
	Enemy();
	void spawn_zombie(float elapsed, GameWindow* gameWindow, sf::Sprite playerSpr, int* playerHealth);
	void draw_zomb(GameWindow* gameWindow);
	void zomb_damage(int damage, float elapsed, bool canBeHit);
	sf::Texture tZombie;
	sf::Sprite sZombie;
	sf::IntRect zombieRect;
	float animationSpeed;
	float zHealth;
};


//Game class declaring variables
class Game : Enemy{

	sf::Font font;

	sf::View view;

	sf::Texture bgImage_1, bgImage_2;
	sf::Sprite backgroundP1, backgroundP2;

	sf::Texture tInstructions1, tInstructions2;
	sf::Sprite sInstructions1, sInstructions2;

	sf::Texture tPlayerIdle;
	sf::Texture tPlayerRunningRight, tPlayerRunningLeft;
	int sprites;
	sf::Sprite sPlayer;
	sf::IntRect playerRect;
	int playerHealth;

	bool running;

	sf::Texture tPlayerFiringRight, tPlayerFiringLeft;
	bool shooting;

	sf::Texture tHealthBar;
	sf::Sprite sHealthBar;
	sf::FloatRect HealthBarCoords;
	sf::RectangleShape fillingHealthBar;
	float healthPercentage;

	float playerSpeed;
	float playerJumpHeight;
	bool reachedJumpHeight;
	bool jumped;

	float firingRate;


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
	int Wave1Index;
	std::vector<Enemy*> Wave1Zombies;
	sf::RectangleShape dWave1Door1, dWave1Door2;
	sf::FloatRect Wave1Door1, Wave1Door2;

protected:
	GameWindow* gameWin;
	void set_values();
	void loop_events();
	void draw_all();

public:
	Game();
	~Game();
	bool gunCanShoot;
	bool gameOpen;
	void start_game(GameWindow* gameWindow);


};

