#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Constants.h"
#include <assert.h>
#include <random>

class Level
{
public:
	Level();
	//~Level();
	int GetWidth();
	int GetHeight();
	void Draw(sf::RenderTarget& rt);
	bool MoveAndAdd();
private:
	const int levelWidth;
	const int levelHeight;
	const int blockWidth;
	const int blockHeight;
	bool Move();
	void CreateNewItems();
	int nGridItems;
	sf::RectangleShape blockShape;

	enum class LevelItemType
	{
		empty,
		extraball,
		block
	};
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
		void DamegeBlock();
		LevelItemType GetType();
		void Draw(sf::RenderTarget& rt, const int x, const int y);
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
