#include "Balls.h"

Balls::Balls(const unsigned int amount, sf::CircleShape newShape)
	:
	nBalls(amount)
{
	BallVec.resize(nBalls);
	SetBallShape(newShape);
}

void Balls::SetBallShape(sf::CircleShape newShape)
{
	BallShape = newShape;
	radius = BallShape.getRadius();
	BallShape.setOrigin(radius, radius);
}

float Balls::Update(Level& lvl,const float dt)
{
	this->dt = dt;
	Move();
	return Collide(lvl);
}

void Balls::Move()
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		BallVec[i].Move(dt);
	}
}

float Balls::Collide(Level& lvl)
{
	CollideWithLevel(lvl);
	return CheckBorderCollision(lvl);
}

void Balls::ResetTimers()
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		BallVec[i].ResetTime();
	}
}

void Balls::Draw(sf::RenderTarget& rt)
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		if (BallVec[i].GetActive())
		{
			BallShape.setPosition(BallVec[i].GetPos());
			rt.draw(BallShape);
		}
	}
}

void Balls::SetAll(sf::Vector2f pos, sf::Vector2f vel)
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		BallVec[i].SetPos(pos);
		BallVec[i].SetVel(vel);
	}
}

bool Balls::ActiveOr()
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		if (BallVec[i].GetActive())
		{
			return true;
		}
	}
	return false;
}

bool Balls::ActiveAnd()
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		if (!BallVec[i].GetActive())
		{
			return false;
		}
	}
	return true;
}

float Balls::CheckBorderCollision(Level& lvl)
{
	const int width = Constants::LevelWidth * Constants::BlockWidth;
	const int height = Constants::LevelHeight * Constants::BlockHeight;
	float lowestTime = -1.0f;
	unsigned int bestBall = -1;
	for (unsigned int i = 0; i < nBalls; i++)
	{
		if (BallVec[i].GetActive())
		{
			float time = BallVec[i].CheckBorderCollision(width, height, radius, dt);
			if (time < lowestTime || bestBall == -1)
			{
				lowestTime = time;
				bestBall = i;
			}
		}
	}
	if (bestBall != -1)
	{
	return BallVec[bestBall].GetPos().x;
	}
	return -2.0f;
}

void Balls::CollideWithLevel(Level & lvl)
{
	for (unsigned int i = 0; i < nBalls; i++)
	{
		int x = int(BallVec[i].GetPos().x) / Constants::BlockWidth;
		int y = int(BallVec[i].GetPos().y) / Constants::BlockHeight;
		Level::LevelItemType Items[9];
		for (int tx = 0; tx < 3; tx++)
		{
			for (int ty = 0; ty < 3; ty++)
			{
				Items[ty * 3 + tx] = lvl.GetType(x + tx - 1, y + ty - 1);
				if (Items[4] == Level::LevelItemType::block)
				{
					BallVec[i].SetVel(-BallVec[i].GetVel());
				}
			}
		}
	}
}

bool Balls::ActivateNext(const float dt)
{
	BallVec[activatedTill].SetActive(true);
	BallVec[activatedTill].Move(dt);
	if (activatedTill + 1 >= nBalls)
	{
		activatedTill = 0;
		return true;
	}
	else
	{
		activatedTill++;
		return false;
	}
}

sf::Vector2f Balls::Ball::GetPos() const
{
	return pos;
}

sf::Vector2f Balls::Ball::GetVel() const
{
	return vel;
}

void Balls::Ball::SetPos(sf::Vector2f newVal)
{
	pos = newVal;
}

void Balls::Ball::SetVel(sf::Vector2f newVal)
{
	vel = newVal;
}

bool Balls::Ball::GetActive() const
{
	return active;
}

void Balls::Ball::SetActive(bool newVal)
{
	active = newVal;
}

float Balls::Ball::GetTime()
{
	return floorHitTime;
}

void Balls::Ball::ResetTime()
{
	floorHitTime = -1.0f;
}

void Balls::Ball::Move(const float dt)
{
	if (active)
	{
		pos += vel * dt;
	}
}

float Balls::Ball::CheckBorderCollision(const int width, const int height, const float radius, const float dt)
{
	const float rad2 = radius + radius;
	if (pos.x + radius > width)
	{
		pos.x = width + width - rad2 - pos.x;
		vel.x = -vel.x;
	}
	if (pos.x - radius < 0)
	{
		pos.x = rad2 - pos.x;
		vel.x = -vel.x;
	}
	if (pos.y - radius < 0)
	{
		pos.y = rad2 - pos.y;
		vel.y = -vel.y;
	}
	if (pos.y + radius > height)
	{
		active = false;
		pos.x -= (vel.x * dt) * (1.0f - (pos.y + radius - height) / (vel.y * dt));
		return (pos.y + radius - height) / (vel.y * dt);
	}
	return -2.0f;
}
