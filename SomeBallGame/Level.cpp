#include "Level.h"

Level::Level(int x)
	:
	levelWidth(Constants::levelWidth),
	levelHeight(Constants::levelHeight)
{
	LevelGrid.resize(levelWidth * (levelHeight - 2));
}

int Level::GetWidth()
{
	return levelWidth;
}

int Level::GetHeight()
{
	return levelHeight;
}

void Level::Draw(sf::RenderTarget & rt)
{

}

Level::LevelItem::LevelItem(const LevelItemType type)
	:
	type(type)
{
}

Level::LevelItem::LevelItem(const unsigned int maxHealth)
{
	block = new Block(maxHealth);
}


Level::LevelItem::~LevelItem()
{
	delete block;
	block = nullptr;
}

void Level::LevelItem::DamegeBlock()
{
	assert(block != nullptr);
	if (block->Damage())
	{
	delete block;
	block = nullptr;
	type = LevelItemType::empty;
	}
}

Level::Block::Block(const unsigned int maxHealth)
	:
	health(maxHealth),
	maxHealth(maxHealth)
{
}

bool Level::Block::Damage()
{
	if (--health <= 0)
	{
		return true;
	}
	return false;
}
