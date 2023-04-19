#include "Game.h"

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

	//backgroundP1.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
	backgroundP1.setPosition(sf::Vector2f(0, 0));
	backgroundP2.setPosition(sf::Vector2f(9600, 0));

	view.reset(sf::FloatRect(0, 0, 1920, 1080));

}

void Game::loop_events() {
	sf::Event event;
	while (gameWin->window.pollEvent(event) && gameOpen)
	{
		if (event.type == sf::Event::Closed) {
			gameWin->window.close();
		}

		sf::FloatRect tempViewPort(view.getCenter().x, view.getCenter().y, 1.0f, 1.0f);
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect tempview(view.getCenter().x, view.getCenter().y, 1.0, 1.0);
			view = gameWin->calculate_viewport();
			gameWin->window.setView(view);
		}
		else {
			gameWin->window.setView(view);
		}


		//gameWin->update_mouse();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			view.move(10, 0);
		}



	}



}

void Game::draw_all() {


	gameWin->window.clear();

	gameWin->window.draw(backgroundP1);
	gameWin->window.draw(backgroundP2);

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