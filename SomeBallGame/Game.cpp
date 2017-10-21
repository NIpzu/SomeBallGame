#include "Game.h"
#include "Constants.h"
#include <cmath>

Game::Game(sf::RenderWindow& win)
	:
	win(win),
	clearColor(0, 0, 0, 255),
	BallShape(Constants::ballRadius, int(Constants::ballRadius) * 4),
	balls(50, BallShape),
	pressShape(6.0f, 20),
	levelHeight(Constants::levelHeight * 100),
	levelWidth(Constants::levelWidth * 100),
	updateInterval(Constants::updateInterval),
	ballSpeed(Constants::ballSpeed),
	level(Constants::levelWidth, Constants::levelHeight),
	ballRadius(Constants::ballRadius),
	ballStartingHeight(Constants::levelHeight * 100 - Constants::ballRadius),
	ballStartingWidth(float(Constants::levelWidth * 50)),
	freeingInterval(Constants::freeingInterval)
{
	pressShape.setOrigin(3.0f, 3.0f);
	pressShape.setFillColor(sf::Color(255, 255, 255, 125));
	line[0] = sf::Vertex(sf::Vector2f(float(levelWidth / 2), float(levelHeight) - ballRadius), sf::Color::White);
}

void Game::StartLoop()
{
	looping = true;
	while (looping)
	{
		if ((sinceLastUpdate += clock.restart().asSeconds()) > updateInterval)
		{
			sinceLastUpdate -= updateInterval;
			Clear();
			Update();
			Draw();
			Dislpay();
		}
		else
		{
			Clear();
			Update();
			Draw();
			Dislpay();
			sinceLastUpdate = 0.0f;
		}
	}
}

void Game::Clear()
{
	win.clear(clearColor);
}

void Game::Update()
{
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || !win.isOpen())
	{
		looping = false;
	}







	if (phase == Phase::waiting && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		phase = Phase::pressing;
		mousePress = sf::Mouse::getPosition(win);
		pressShape.setPosition(sf::Vector2f(float(mousePress.x), float(mousePress.y)));
		BallShape.setPosition(ballStartingWidth - ballRadius, ballStartingHeight - ballRadius);
	}


	if (phase == Phase::pressing)
	{
		sf::Vector2f mouseDirection(mousePress - sf::Mouse::getPosition(win));
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mouseDirection *= (1.0f / std::sqrt(mouseDirection.x * mouseDirection.x + mouseDirection.y * mouseDirection.y));
			balls.SetAll(sf::Vector2f(ballStartingWidth, ballStartingHeight), mouseDirection * ballSpeed);
			phase = Phase::freeing;
			freeingTimer = 0.0f;
		}
		else
		{
			line[1] = sf::Vertex(sf::Vector2f(ballStartingWidth, ballStartingHeight) + mouseDirection, sf::Color::Black);
		}
	}
	
	if (phase == Phase::freeing)
	{
		if (freeingTimer >= freeingInterval)
		{
			freeingTimer -= freeingInterval;

			if (balls.ActivateNext())
			{
				phase = Phase::playing;
			}

		}

		freeingTimer += sinceLastUpdate;
	}
	else if (newBallStartingWidth > -1.0f)
	{
		ballStartingWidth = newBallStartingWidth;
		newBallStartingWidth = -2.0f;
		line[0] = sf::Vertex(sf::Vector2f(ballStartingWidth, float(levelHeight - ballRadius)), sf::Color::White);
	}







	if (phase == Phase::playing || phase == Phase::freeing)
	{
		float updateReturn = balls.Update(level,sinceLastUpdate);
		if (updateReturn > -1.0f && newBallStartingWidth < -1.0f)
		{
			newBallStartingWidth = updateReturn;
		}
		if (!balls.ActiveOr() && phase == Phase::playing)
		{
			phase = Phase::waiting;
		}
	}


}

void Game::Draw()
{
	if (phase == Phase::pressing)
	{
		win.draw(pressShape);
		win.draw(line, 2, sf::Lines);
		win.draw(BallShape);
	}
	if (phase == Phase::freeing || phase == Phase::playing)
	{
		balls.Draw(win);
	}
}

void Game::Dislpay()
{
	win.display();
}
