#pragma once
#include <SFML\Graphics.hpp>
#include "Balls.h"
#include "Level.h"

class Game
{
public:
	Game(sf::RenderWindow& win);
	void StartLoop();
private:
	void Clear();
	void Update();
	void Draw();
	void Dislpay();
	sf::RenderWindow& win;
	sf::Color clearColor;
	sf::CircleShape BallShape;
	Balls balls;
	float sinceLastUpdate;
	bool looping = false;
	sf::Clock clock;
	sf::Vector2i mousePress;
	sf::Vector2i mouseRelease;
	sf::CircleShape pressShape;
	sf::Vertex line[2];
	Level level;
	enum class Phase
	{
		pressing,
		freeing,
		playing,
		waiting
	};
	float newBallStartingWidth = -2.0f;
	float freeingTimer = 0.0f;
	float ballStartingWidth;
	const float ballStartingHeight;
	const int levelWidth;
	const int levelHeight;
	const float updateInterval;
	const float ballSpeed;
	const float ballRadius;
	const float freeingInterval;
	Phase phase = Phase::waiting;
};