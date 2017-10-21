#include "Level.h"

Level::Level()
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
{
}

Level::LevelItem::LevelItem(const Block * const block)
{
}

Level::LevelItem::~LevelItem()
{
	delete block;
}

void Level::LevelItem::DestroyBlock()
{
	assert(block != nullptr);
	delete block;
	type = LevelItemType::empty;
}

Level::Block::Block(const unsigned int maxHealth)
	:
	health(maxHealth),
	maxHealth(maxHealth)
{
}
