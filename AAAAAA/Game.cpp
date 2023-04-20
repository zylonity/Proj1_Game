#include "Game.h"
#include <iostream>


sf::RectangleShape dWave1Door1;
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

	floorTest[0] = sf::FloatRect(0, 0, 30, 1080);
	floorTest[1] = sf::FloatRect(0, 1048, 4755, 30);
	floorTest[2] = sf::FloatRect(4755, 1005, 100, 75);
	floorTest[3] = sf::FloatRect(4855, 950, 90, 130);
	floorTest[4] = sf::FloatRect(4945, 895, 83, 185);
	floorTest[5] = sf::FloatRect(5028, 852, 92, 228);
	floorTest[6] = sf::FloatRect(5119, 851, 1849, 30);
	floorTest[7] = sf::FloatRect(6968, 851, 78, 190);
	floorTest[8] = sf::FloatRect(7045, 890, 78, 190);
	floorTest[9] = sf::FloatRect(7122, 939, 93, 141);
	floorTest[10] = sf::FloatRect(7214, 996, 99, 84);
	floorTest[11] = sf::FloatRect(7313, 1049, 11887, 30);
	floorTest[12] = sf::FloatRect(19170, 0, 30, 1080);

	Wave1Door1 = sf::FloatRect(2162, 764, 30, 282);
	Wave1Door2 = sf::FloatRect(3942, 754, 30, 295);


	for (int i = 0; i < 13; i++) {
		floorDisplay[i].setSize(sf::Vector2f(floorTest[i].width, floorTest[i].height));
		floorDisplay[i].setPosition(floorTest[i].left, floorTest[i].top);
		floorDisplay[i].setFillColor(sf::Color(100, 250, 50));
		
	}



	dWave1Door1.setSize(sf::Vector2f(Wave1Door1.width, Wave1Door1.height));
	dWave1Door1.setPosition(Wave1Door1.left, Wave1Door1.top);
	dWave1Door1.setFillColor(sf::Color(100, 250, 50));



	sPlayer.setPosition(view.getCenter().x, 765);

	playerHealth = 100;
	cameraSpeed = 1000;
	playerSpeed = 400.f;

	//The smaller the faster
	animSpeed = 0.3f;

	accelerationSpeed = 200.f;

	wave1Active = false;
	wave1TimeToWait = 5.f;
	wave1Timer = 0.f;
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



		for (int i = 1; i < 12; i++) {
			if (i <= 6) {
				if (sPlayer.getGlobalBounds().left + 100 >= floorTest[i].left) {
					sPlayer.setPosition(sPlayer.getPosition().x, floorTest[i].top - 285);
				}
			}
			else if (i >= 7) {
				if (sPlayer.getGlobalBounds().left >= floorTest[i].left) {
					sPlayer.setPosition(sPlayer.getPosition().x, floorTest[i].top - 285);
				}
			}
			

		}



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

			if (sPlayer.getGlobalBounds().intersects(floorTest[12])) {
				acceleration.x = 0;
				velocity.x = 0;

			}
			else {
				if (velocity.x < playerSpeed) {
					acceleration.x += accelerationSpeed * timeSinceLastFrame;
				}
			}

			if (wave1Active) {
				if (sPlayer.getGlobalBounds().intersects(Wave1Door2)) {
					acceleration.x = 0;
					velocity.x = 0;

				}
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (sPlayer.getGlobalBounds().intersects(floorTest[0])) {
				acceleration.x = 0;
				velocity.x = 0;

			}
			else {
				if (-velocity.x < playerSpeed) {
					acceleration.x -= accelerationSpeed * timeSinceLastFrame;
				}
			}

			if (wave1Active) {
				if (sPlayer.getGlobalBounds().intersects(Wave1Door1)) {
					acceleration.x = 0;
					velocity.x = 0;

				}
			}
			

		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (acceleration.x > 0) {
				acceleration.x -= accelerationSpeed * timeSinceLastFrame;
			}

			if (acceleration.x < 0) {
				acceleration.x += accelerationSpeed * timeSinceLastFrame;
			}
		}

		view.setCenter(sPlayer.getPosition().x, 540);
		gameWin->window.setView(view);

		if (velocity.x >= playerSpeed) {
			velocity.x = playerSpeed;

		}

		velocity += acceleration;

		velocity = 0.8f * velocity;

		//Wave 1
		if (sPlayer.getGlobalBounds().left - 100 >= Wave1Door1.left) {
			wave1Active = true;
		}

		if (wave1Active) {
			wave1Timer += timeSinceLastFrame;
			if (wave1Timer >= wave1TimeToWait) {
				Wave1Zombies.push_back(new Enemy());
				
				wave1Timer = 0;
			}

			for (int i = 0; i < Wave1Zombies.size(); i++) {
				Wave1Zombies[i]->spawn_zombie(timeSinceLastFrame, animSpeed, gameWin, sPlayer.getPosition());
			}

		}

		sPlayer.setPosition(sf::Vector2f(sPlayer.getPosition() + (velocity * timeSinceLastFrame)));



	}





}

void Game::draw_all() {


	gameWin->window.clear();

	//Could be more optimized by drawing the second background later on, but its okay
	gameWin->window.draw(backgroundP1);
	gameWin->window.draw(backgroundP2);

	//Draw player
	gameWin->window.draw(sPlayer);

	gameWin->window.draw(dWave1Door1);

	//

	for (int i = 0; i < Wave1Zombies.size(); i++) {
		Wave1Zombies[i]->draw_zomb(gameWin);
	}

	for (int i = 0; i < 13; i++) {
		gameWin->window.draw(floorDisplay[i]);
	}
	

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

Enemy::Enemy() {
	tZombie.loadFromFile("Resources/Textures/Zombie/ZombieIdle.png");
	sZombie.setTexture(tZombie);

	zombieRect = sf::IntRect(0, 0, 100, 285);
	sZombie.setTextureRect(zombieRect);
	zHealth = 100;
	justSpawned = true;
	moveSpeed = 200.f;
}


void Enemy::spawn_zombie(float lastFrameTime, float aniTime, GameWindow* zGameWin, sf::Vector2f playerCoords) {
	float yAxis = playerCoords.y;

	gameWW = zGameWin;
	if (justSpawned == true) {
		bool TrueFalse = (rand() % 100) < 50;
		if (TrueFalse) {
			sZombie.setPosition(zGameWin->window.getView().getCenter().x + (zGameWin->window.getView().getSize().x / 2), yAxis);
		}
		else {
			sZombie.setPosition(zGameWin->window.getView().getCenter().x - (zGameWin->window.getView().getSize().x / 2), yAxis);
		}

		justSpawned = false;
	}

	elapsed += lastFrameTime;

	if (elapsed > aniTime) {
		if (zombieRect.left < 400) {
			zombieRect.left += 100;
			sZombie.setTextureRect(zombieRect);
		}

		if (zombieRect.left == 400) {
			zombieRect.left = 0;
			sZombie.setTextureRect(zombieRect);
		}
		elapsed = 0;

	}
	
	if (sZombie.getPosition().x > playerCoords.x + 50) 
	{
		sZombie.setPosition(sf::Vector2f(sZombie.getPosition().x - (lastFrameTime * moveSpeed), sZombie.getPosition().y));
	}
	else if (sZombie.getPosition().x < playerCoords.x - 50) 
	{
		sZombie.setPosition(sf::Vector2f(sZombie.getPosition().x + (lastFrameTime * moveSpeed), sZombie.getPosition().y));
	}

}

void Enemy::draw_zomb(GameWindow* gameWaa) {
	sZombie.setTexture(tZombie);
	gameWaa->window.draw(sZombie);
}