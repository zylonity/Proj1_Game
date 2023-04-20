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

	//Map backgrounds
	bgImage_1.loadFromFile("Resources/Textures/Game/map1.png");
	bgImage_2.loadFromFile("Resources/Textures/Game/map2.png");
	backgroundP1.setTexture(bgImage_1);
	backgroundP2.setTexture(bgImage_2);

	//Due to the images being large, map is split in 2
	backgroundP1.setPosition(0, 0);
	backgroundP2.setPosition(9600, 0);

	tInstructions1.loadFromFile("Resources/Textures/UI/Instructions1.png");
	tInstructions2.loadFromFile("Resources/Textures/UI/Instructions2.png");
	sInstructions1.setTexture(tInstructions1);
	sInstructions2.setTexture(tInstructions2);

	sInstructions1.setPosition(400, 200);
	sInstructions2.setPosition(1200, 300);

	//Player animations
	tPlayerIdle.loadFromFile("Resources/Textures/Player/PlayerIdle.png");
	tPlayerRunningRight.loadFromFile("Resources/Textures/Player/PlayerRunningRight.png");
	tPlayerRunningLeft.loadFromFile("Resources/Textures/Player/PlayerRunningLeft.png");
	sPlayer.setTexture(tPlayerIdle);
	sprites = 5;

	running = false;

	//Player sprites are 100 x 285 per sheet
	playerRect = sf::IntRect(0, 0, 100, 285);
	sPlayer.setTextureRect(playerRect);

	//UI, Health bar and instructions
	tHealthBar.loadFromFile("Resources/Textures/UI/EmptyHealth3.png");
	sHealthBar.setTexture(tHealthBar);
	HealthBarCoords = sf::FloatRect(30, 97, 325, 60);
	
	//Basic physics
	acceleration = sf::Vector2f(0, 0);
	velocity = sf::Vector2f(0, 0);

	view.reset(sf::FloatRect(0, 0, 1920, 1080));


	//Map boundaries
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

	//Helps visualise the map boundaries
	/*for (int i = 0; i < 13; i++) {
		floorDisplay[i].setSize(sf::Vector2f(floorTest[i].width, floorTest[i].height));
		floorDisplay[i].setPosition(floorTest[i].left, floorTest[i].top);
		floorDisplay[i].setFillColor(sf::Color(100, 250, 50));
		
	}*/


	//Visualise wave 1 doors
	dWave1Door1.setSize(sf::Vector2f(Wave1Door1.width, Wave1Door1.height));
	dWave1Door1.setPosition(Wave1Door1.left, Wave1Door1.top);
	dWave1Door1.setFillColor(sf::Color(100, 250, 50));

	dWave1Door2.setSize(sf::Vector2f(Wave1Door2.width, Wave1Door2.height));
	dWave1Door2.setPosition(Wave1Door2.left, Wave1Door2.top);
	dWave1Door2.setFillColor(sf::Color(100, 250, 50));



	//Initial player spawn and variables
	sPlayer.setPosition(view.getCenter().x, 765);
	playerHealth = 100;
	playerSpeed = 400.f;
	accelerationSpeed = 200.f;

	//The smaller the faster
	animSpeed = 0.3f;


	//Wave 1 details
	wave1Active = false;
	wave1TimeToWait = 5.f;
	wave1Timer = 0.f;
	Wave1Index = 0;

	gunCanShoot = true;

}



void Game::loop_events() {

	//Getting the time to make the game FPS independent.
	timeSinceLastFrame = clock.restart().asSeconds();
	elapsedTime += timeSinceLastFrame;

	gameWin->update_mouse();

	sf::Event event;
	while (gameWin->window.pollEvent(event) && gameOpen)
	{
		if (event.type == sf::Event::Closed) {
			gameWin->window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {

			//damage zombies
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				for (int i = 0; i < Wave1Zombies.size(); i++) {
					if (Wave1Zombies[i]->sZombie.getGlobalBounds().contains(gameWin->mouseCoords)) {
						Wave1Zombies[i]->zomb_damage(10, timeSinceLastFrame, gunCanShoot);
						if (Wave1Zombies[i]->zHealth <= 0) {
							Wave1Zombies.erase(Wave1Zombies.begin() + i);
						}
					}
				}
			}
		}

	}


	if (playerHealth > 0) {

		//Places health bar sprite and deals with visual rectangle for health
		sHealthBar.setPosition(view.getCenter().x - (view.getSize().x / 2) + 70, view.getCenter().y - (view.getSize().y / 2) + 70);
		fillingHealthBar.setSize(sf::Vector2f((HealthBarCoords.width / 100) * playerHealth, HealthBarCoords.height));
		fillingHealthBar.setPosition(HealthBarCoords.left + sHealthBar.getPosition().x, HealthBarCoords.top + sHealthBar.getPosition().y);
		fillingHealthBar.setFillColor(sf::Color(179, 0, 0));


		//Deals with the stairs in the map, fixes visual bug
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

		

		//Deal with animations
		if (elapsedTime > animSpeed) {
			if (playerRect.left < (sprites * 100) - 100) {
				playerRect.left += 100;
				sPlayer.setTextureRect(playerRect);
			}

			if (playerRect.left >= (sprites * 100) - 100) {
				playerRect.left = 0;
				sPlayer.setTextureRect(playerRect);
			}
			elapsedTime = 0;

		}


		//Deals with right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//update sprite accordingly
			sprites = 7;
			animSpeed = 0.1f;
			sPlayer.setTexture(tPlayerRunningRight);


			//Deals with wall at the very end of the map
			if (sPlayer.getGlobalBounds().intersects(floorTest[12])) {
				acceleration.x = 0;
				velocity.x = 0;

			}
			else {
				if (velocity.x < playerSpeed) {
					acceleration.x += accelerationSpeed * timeSinceLastFrame; //Deaccelerate player accordingly
				}
			}

			//Deals with door on the right for each wave
			if (wave1Active) {
				if (sPlayer.getGlobalBounds().intersects(Wave1Door2)) {
					acceleration.x = 0;
					velocity.x = 0;

				}
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sprites = 7;
			animSpeed = 0.1f;
			sPlayer.setTexture(tPlayerRunningLeft);

			//Deals with wall at the very beginning of the map
			if (sPlayer.getGlobalBounds().intersects(floorTest[0])) {
				acceleration.x = 0;
				velocity.x = 0;

			}
			else {
				if (-velocity.x < playerSpeed) {
					acceleration.x -= accelerationSpeed * timeSinceLastFrame;
				}
			}

			//Deals with door on the left for each wave
			if (wave1Active) {
				if (sPlayer.getGlobalBounds().intersects(Wave1Door1)) {
					acceleration.x = 0;
					velocity.x = 0;

				}
			}
			

		}


		//Deals with no player input
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		{
			if (acceleration.x > 0) {
				acceleration.x -= accelerationSpeed * timeSinceLastFrame;
			}

			if (acceleration.x < 0) {
				acceleration.x += accelerationSpeed * timeSinceLastFrame;
			}

			sprites = 5;
			animSpeed = 0.3f;
			sPlayer.setTexture(tPlayerIdle);
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

			dWave1Door1.setFillColor(sf::Color(153, 24, 15));
			dWave1Door2.setFillColor(sf::Color(153, 24, 15));

			wave1Timer += timeSinceLastFrame;
			if (wave1Timer >= wave1TimeToWait && Wave1Index != 6) {
				Wave1Zombies.push_back(new Enemy()); //Adds an instance of the enemy class to a vector to spawn in
				Wave1Index += 1;
				wave1Timer = 0;
			}

			//Keeps zombies alive during the wave
			for (int i = 0; i < Wave1Zombies.size(); i++) {
				Wave1Zombies[i]->spawn_zombie(timeSinceLastFrame, gameWin, sPlayer, &playerHealth);
			}

			if (Wave1Index == 6 && Wave1Zombies.size() == 0) {
				dWave1Door1.setFillColor(sf::Color::Transparent);
				dWave1Door2.setFillColor(sf::Color::Transparent);
				wave1Active = false;
			}
		}
		//Deal with player movement at the very end of the update
		sPlayer.setPosition(sf::Vector2f(sPlayer.getPosition() + (velocity * timeSinceLastFrame)));
	}
}

void Game::draw_all() {


	gameWin->window.clear();

	//Could be more optimized by drawing the second background later on, but its okay for now
	gameWin->window.draw(backgroundP1);
	gameWin->window.draw(backgroundP2);

	gameWin->window.draw(sInstructions1);
	gameWin->window.draw(sInstructions2);

	//Draw player
	gameWin->window.draw(sPlayer);
	gameWin->window.draw(fillingHealthBar);
	gameWin->window.draw(sHealthBar);


	gameWin->window.draw(dWave1Door1);
	gameWin->window.draw(dWave1Door2);

	//

	for (int i = 0; i < Wave1Zombies.size(); i++) {
		Wave1Zombies[i]->draw_zomb(gameWin); //Have to call a function inside the class otherwise the texture isn't loaded properly
	}

	for (int i = 0; i < 13; i++) {
		gameWin->window.draw(floorDisplay[i]);
	}
	

	gameWin->window.display();
}

//Start code
void Game::start_game(GameWindow* tGameWin) {
	gameWin = tGameWin;
	gameOpen = true;
	while (gameWin->window.isOpen() && gameOpen)
	{
		loop_events();
		draw_all();
	}
}

//Defines enemy caller
Enemy::Enemy() {
	tZombie.loadFromFile("Resources/Textures/Zombie/ZombieIdle.png");
	sZombie.setTexture(tZombie);


	elapsed = 0;
	zombieRect = sf::IntRect(0, 0, 100, 285);
	sZombie.setTextureRect(zombieRect);
	zHealth = 100;
	justSpawned = true;
	moveSpeed = 200.f;

	animationSpeed = 0.3f;

	damageCooldown = 1;
	damageCooldownTimer = 0.f;

	damageAnimTime = 0;
}

//Enemy spawn code
void Enemy::spawn_zombie(float lastFrameTime, GameWindow* zGameWin, sf::Sprite playerSpr, int* playerHealth) {
	sf::Vector2f playerCoords(playerSpr.getGlobalBounds().left, playerSpr.getGlobalBounds().top);
	float yAxis = playerCoords.y;

	if (justSpawned == true) {
		bool TrueFalse = (rand() % 100) < 50; //Random chance of spawning either left or right
		if (TrueFalse) {
			sZombie.setPosition(zGameWin->window.getView().getCenter().x + (zGameWin->window.getView().getSize().x / 2), yAxis); //Spawns outside camera view
		}
		else {
			sZombie.setPosition(zGameWin->window.getView().getCenter().x - (zGameWin->window.getView().getSize().x / 2), yAxis);
		}

		justSpawned = false;
	}

	elapsed += lastFrameTime;


	//Deals with zombie animations
	if (elapsed > animationSpeed) {
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

	damageCooldownTimer += lastFrameTime;
	if (damageCooldownTimer >= damageCooldown) {
		if (sZombie.getGlobalBounds().intersects(playerSpr.getGlobalBounds())) {
			*playerHealth -= 5;
		}
		damageCooldownTimer = 0;
	}


}

void Enemy::zomb_damage(int damage, float lastFrameTime, bool canBeHit) {

	if (canBeHit) {
		zHealth -= damage;
		canBeHit = false;
	}

	damageAnimTime += lastFrameTime;
	if (damageAnimTime < 0.7f) {
		sZombie.setColor(sf::Color(13, 115 + ((damageAnimTime * 0.5f) * 100), 0));
		canBeHit = true;
	}
	else {
		sZombie.setColor(sf::Color(13, 115, 0));
		damageAnimTime = 0;
	}

	if (zHealth <= 0) {
		sZombie.setColor(sf::Color(0, 17, 14));
	}


}

void Enemy::draw_zomb(GameWindow* gameWaa) {
	sZombie.setTexture(tZombie);
	gameWaa->window.draw(sZombie);
}