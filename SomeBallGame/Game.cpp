#include "Game.h"

Game::Game(sf::RenderWindow& win)
	:
	win(win),
	clearColor(0, 0, 0, 255),
	pressShape(6.0f, 20),
	levelHeight(Constants::LevelHeight * Constants::BlockHeight),
	levelWidth(Constants::LevelWidth * Constants::BlockWidth),
	updateInterval(Constants::UpdateInterval),
	ballSpeed(Constants::BallSpeed),
	ballRadius(Constants::BallRadius),
	ballStartingHeight(Constants::LevelHeight * Constants::BlockWidth - Constants::BallRadius),
	ballStartingWidth(float(Constants::LevelWidth * Constants::BlockWidth / 2)),
	freeingInterval(Constants::FreeingInterval),
	BallShape(Constants::BallRadius, int(Constants::BallRadius) * 4),
	balls(50, BallShape)
{
	pressShape.setOrigin(3.0f, 3.0f);
	pressShape.setFillColor(sf::Color(255, 255, 255, 125));
	line[0] = sf::Vertex(sf::Vector2f(float(levelWidth / 2), float(levelHeight) - ballRadius), sf::Color::White);
	font.loadFromFile("arial.ttf");
	fpsCounter.setFont(font);
	fpsCounter.setCharacterSize(20);
	fpsCounter.setPosition(20.0f, 20.0f);
}

void Game::StartLoop()
{
	looping = true;
	while (looping)
	{
		sinceLastRestart = clock.restart().asSeconds();
		if ((sinceLastUpdate += sinceLastRestart) > updateInterval)
		{
			dt = updateInterval;
		}
		else
		{
			dt = sinceLastUpdate;
		}
		if ((sinceFpsCount += sinceLastRestart) > 1.0f)
		{
			fps = updatesLastSecond;
			sinceFpsCount = 0.0f;
			updatesLastSecond = 0;
		}
		else
		{
			updatesLastSecond++;
		}
		fpsCounter.setString(std::to_string(fps));
		Clear();
		Update();
		Draw();
		Dislpay();
		sinceLastUpdate = 0.0f;
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







	if (phase == Phase::playing || phase == Phase::freeing)
	{
		float updateReturn = balls.Update(level, dt);
		if (updateReturn > -1.0f && newBallStartingWidth < -1.0f)
		{
			newBallStartingWidth = updateReturn;
		}
		if (!balls.ActiveOr() && phase == Phase::playing)
		{
			phase = Phase::waiting;
			if (level.MoveAndAdd())
			{
				//yee you lose
			}
		}
	}




	if (phase == Phase::freeing)
	{
		freeingTimer += dt;

		if (freeingTimer >= freeingInterval)
		{
			freeingTimer -= freeingInterval;
			if (balls.ActivateNext(freeingTimer))
			{
				phase = Phase::playing;
			}

		}

	}
	else if (newBallStartingWidth > -1.0f)
	{
		ballStartingWidth = newBallStartingWidth;
		newBallStartingWidth = -2.0f;
		line[0] = sf::Vertex(sf::Vector2f(ballStartingWidth, float(levelHeight - ballRadius)), sf::Color::White);
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
	level.Draw(win);
	win.draw(fpsCounter);
}

void Game::Dislpay()
{
	win.display();
}
