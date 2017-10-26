#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Level.h"

class Balls
{
public:
	Balls(const unsigned int amount, sf::CircleShape newShape);
	void SetBallShape(sf::CircleShape newShape);
	float Update(Level& lvl,const float dt);
	void Draw(sf::RenderTarget& rt);
	void SetAll(sf::Vector2f pos, sf::Vector2f vel);
	bool ActiveOr();
	bool ActiveAnd();
	bool ActivateNext(const float dt);
private:
	float Collide(Level& lvl);
	float CheckBorderCollision(Level& lvl);
	void CollideWithLevel(Level& lvl);
	void Move();
	void ResetTimers();
	class Ball
	{
	public:
		sf::Vector2f GetPos() const;
		sf::Vector2f GetVel() const;
		void SetPos(sf::Vector2f newVal);
		void SetVel(sf::Vector2f newVal);
		bool GetActive() const;
		void SetActive(bool newVal);
		float GetTime();
		void ResetTime();
		void Move(const float dt);
		float CheckBorderCollision(const int widht, const int height, const float radius, const float dt);
	private:
		sf::Vector2f pos;
		sf::Vector2f vel;
		bool active = false;
		float floorHitTime = -1.0f;
	};

	std::vector<Ball> BallVec;
	unsigned int nBalls;
	float dt;
	float radius;
	sf::CircleShape BallShape;
	unsigned int activatedTill = 0;
};