#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "Game.h"
#include "Constants.h"


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	sf::RenderWindow window(sf::VideoMode(Constants::LevelWidth * 100, Constants::LevelHeight * 100), "SFML window", sf::Style::None, sf::ContextSettings::ContextSettings(0, 0, 8));

	Game game(window);
	game.StartLoop();

	window.close();
}