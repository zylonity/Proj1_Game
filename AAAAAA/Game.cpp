#include "Game.h"
#include <iostream>

//set pointers
Game::Game() {

	gameOpen = true;

	set_values();
}


//delete pointers
Game::~Game() {


}

void Game::set_values() {

	bgImage_1.loadFromFile("Resources/Textures/Game/map1.png");
	bgImage_2.loadFromFile("Resources/Textures/Game/map2.png");
	backgroundP1.setTexture(bgImage_1);
	backgroundP2.setTexture(bgImage_2);

	backgroundP1.setPosition(0, 0);
	backgroundP2.setPosition(9600, 0);

	tPlayerIdle.loadFromFile("Resources/Textures/Player/PlayerIdle.png");
	sPlayer.setTexture(tPlayerIdle);

	playerRect = sf::IntRect(0, 0, 100, 285);
	sPlayer.setTextureRect(playerRect);
	
	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);

	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	floorTest = sf::FloatRect(0, 1048, 4755, 31);
	floor.setSize(sf::Vector2f(4755, 31));
	floor.setPosition(0, 1048);

	floor.setFillColor(sf::Color(100, 250, 50));


	sPlayer.setPosition(view.getCenter());

	playerHealth = 100;
	cameraSpeed = 1000;
	playerSpeed = 1;

	//The smaller the faster
	animSpeed = 0.3;

	gravity = 100;


	accelerationSpeed = 3.f;
}



void Game::loop_events() {

	//Getting the time to make the game FPS independent.
	timeSinceLastFrame = clock.restart().asSeconds();
	elapsedTime += timeSinceLastFrame;


	sf::Event event;
	while (gameWin->window.pollEvent(event) && gameOpen)
	{
		if (event.type == sf::Event::Closed) {
			gameWin->window.close();
		}
	}

	if (playerHealth > 0) {




		if (sPlayer.getGlobalBounds().intersects(floorTest)) {

		}
		else {
			sPlayer.setPosition(sf::Vector2f(sPlayer.getPosition().x, sPlayer.getPosition().y + (gravity * timeSinceLastFrame)));
		}
		//Gravity


		//Deal with idle animation
		if (elapsedTime > animSpeed) {
			if (playerRect.left < 400) {
				playerRect.left += 100;
				sPlayer.setTextureRect(playerRect);
			}

			if (playerRect.left == 400) {
				playerRect.left = 0;
				sPlayer.setTextureRect(playerRect);
			}
			elapsedTime = 0;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (velocity.x < playerSpeed) {
				acceleration.x += accelerationSpeed * timeSinceLastFrame;

			}

			
			//std::cout << velocity.x << " " << acceleration.x << '\n';

		}
		else {
			if (acceleration.x > 0) {
				acceleration.x -= accelerationSpeed * timeSinceLastFrame;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//if (velocity.x > -playerSpeed) {
			//	acceleration.x -= accelerationSpeed * timeSinceLastFrame;
			//	
			//}

		}

		view.setCenter(sPlayer.getPosition().x, 540);
		gameWin->window.setView(view);

		if (velocity.x >= playerSpeed) {
			velocity.x = playerSpeed;

		}

		velocity += acceleration;

		velocity = 0.2f * velocity;

		sPlayer.setPosition(sf::Vector2f(sPlayer.getPosition().x + velocity.x, sPlayer.getPosition().y));
	}





}

void Game::draw_all() {


	gameWin->window.clear();

	//Could be more optimized by drawing the second background later on, but its okay
	gameWin->window.draw(backgroundP1);
	gameWin->window.draw(backgroundP2);

	//Draw player
	gameWin->window.draw(sPlayer);

	gameWin->window.draw(floor);

	gameWin->window.display();
}

void Game::start_game(GameWindow* tGameWin) {
	gameWin = tGameWin;
	gameOpen = true;
	while (gameWin->window.isOpen() && gameOpen)
	{
		loop_events();
		draw_all();
	}
}