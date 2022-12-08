#include "MainMenu_Header.h"
#include <SFML\Graphics.hpp>

int main() {
	MainMenu* menu = new MainMenu();
	menu->run_menu();

	//Once run_menu's done continue here
	delete menu;
	menu = nullptr;
	return 1;
}