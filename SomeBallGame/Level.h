#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Constants.h"
#include <assert.h>
#include <random>

class Level
{
public:
	enum class LevelItemType
	{
		empty,
		extraball,
		block
	};
	Level();
	~Level();
	int GetWidth();
	int GetHeight();
	void Draw(sf::RenderTarget& rt);
	bool MoveAndAdd();
	LevelItemType GetType(const int x, const int y) const;
	void Hit(const int x, const int y);
private:
	const int levelWidth;
	const int levelHeight;
	const int blockWidth;
	const int blockHeight;
	bool Move();
	void CreateNewItems();
	int nGridItems;
	sf::RectangleShape blockShape;
	sf::CircleShape extraBallShape;

	
	class Block
	{
	public:
		Block(const unsigned int maxHealth);
		bool Damage();
	private:
		unsigned int health;
		const unsigned int maxHealth;
	};



	class LevelItem
	{
	public:
		LevelItem(const LevelItemType type, const int maxHealth);
		LevelItem(const LevelItemType type);
		LevelItem(const LevelItem& other);
		LevelItem& operator= (const LevelItem& other);
		LevelItem& operator= (const LevelItemType type);
		~LevelItem();
		void DamageBlock();
		LevelItemType GetType();
	private:
		LevelItemType type;
		Block* block = nullptr;
	};


	int score = 1;

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> Rand;

	std::vector<LevelItem*> LevelGrid;
};
