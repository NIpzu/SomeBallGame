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
	bool Update();
private:
	const int levelWidth;
	const int levelHeight;
	bool Move();
	void CreateNewItems();

	enum class LevelItemType
	{
		empty,
		block,
		extraball,
		last
	};

	class Block
	{
	public:
		Block(const unsigned int maxHealth);
		//void Draw(sf::RenderTarget& rt, const int x, const int y);
		bool Damage();
	private:
		unsigned int health;
		const unsigned int maxHealth;
	};



	class LevelItem
	{
	public:
		LevelItem(const LevelItemType type);
		LevelItem(const unsigned int maxHealth);
		LevelItem(const LevelItem& other);
		LevelItem& operator= (const LevelItem& other);
		LevelItem& operator= (const LevelItemType type);
		~LevelItem();
		void DamegeBlock();
		LevelItemType GetType();
	private:
		LevelItemType type;
		Block* block = nullptr;
	};


	int score = 0;

	std::vector<LevelItem*> LevelGrid;
};
