#include "Level.h"

Level::Level()
	:
	levelWidth(Constants::levelWidth),
	levelHeight(Constants::levelHeight)
{
	LevelGrid.resize(levelWidth * (levelHeight - 2));
	for (int i = 0; i < LevelGrid.size(); i++)
	{
		*LevelGrid[i] = LevelItemType::empty;
	}
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

bool Level::Update()
{
	CreateNewItems();
	return Move();
}

bool Level::Move()
{	
	for (int x = 0; x < levelWidth; x++)
	{
		for (int y = 1; y < levelHeight; y++)
		{
			*LevelGrid[y * levelWidth + x] = *LevelGrid[y * levelWidth - levelWidth + x];
		}
	}
	for (int x = 0; x < levelWidth; x++)
	{
		if (LevelGrid[x + levelHeight * levelWidth - levelWidth]->GetType() == LevelItemType::block)
		{
			return true;
		}
	}
	score++;
	return false;
}

void Level::CreateNewItems()
{
	for (int x = 0; x < levelWidth; x++)
	{
	}
}

Level::LevelItem::LevelItem(const LevelItemType type)
	:
	type(type)
{
	assert(type != LevelItemType::last);
}

Level::LevelItem::LevelItem(const unsigned int maxHealth)
{
	block = new Block(maxHealth);
}

Level::LevelItem::LevelItem(const LevelItem & other)
{
	delete block;
	block = nullptr;
	type = other.type;
	block = other.block;
	assert(type != LevelItemType::last);
}

Level::LevelItem & Level::LevelItem::operator=(const LevelItem & other)
{
	delete block;
	block = nullptr;
	type = other.type;
	block = other.block;
	assert(type != LevelItemType::last);
	return *this;
}

Level::LevelItem & Level::LevelItem::operator=(const LevelItemType type)
{
	delete block;
	block = nullptr;
	this->type = type;
	if (type == LevelItemType::block, type == LevelItemType::block)
	{
		assert(false);
	}
	return *this;
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

Level::LevelItemType Level::LevelItem::GetType()
{
	return type;
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
