#include "Level.h"

Level::Level()
	:
	levelWidth(Constants::LevelWidth),
	levelHeight(Constants::LevelHeight),
	blockWidth(Constants::BlockWidth),
	blockHeight(Constants::BlockHeight),
	blockShape(sf::Vector2f(float(Constants::BlockWidth), float(Constants::BlockHeight)))
{
	nGridItems = levelWidth * levelHeight;
	blockShape.setOrigin(0.0f, 0.0f);
	LevelGrid.resize(levelWidth * levelHeight);
	for (int i = 0; i < nGridItems; i++)
	{
		LevelGrid[i] = new LevelItem(LevelItemType::empty, 0);
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
	for (int i = 0; i < nGridItems; i++)
	{
		int x = i % levelWidth;
		int y = i / levelWidth;
		if (LevelGrid[i]->GetType() == LevelItemType::block)
		{
			blockShape.setPosition(float(x) * blockWidth, float(y) * blockHeight);
			rt.draw(blockShape);
		}
		else
		{
		LevelGrid[i]->Draw(rt, x, y);
		}
	}
}

bool Level::MoveAndAdd()
{
	CreateNewItems();
	return Move();
}

bool Level::Move()
{	
	
	for (int y = levelHeight - levelWidth; y > 0; y--)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			*LevelGrid[y * levelWidth + x] = *LevelGrid[y * levelWidth - levelWidth + x];
		}
	}
	for (int x = 0; x < levelWidth; x++)
	{
		*LevelGrid[x] = LevelItemType::empty;
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
		LevelGrid[x] = new LevelItem(static_cast<LevelItemType>(rand() % int(LevelItemType::last)), score);
	}
}

Level::LevelItem::LevelItem(const LevelItemType type, const int maxHealth)
	:
	type(type)
{
	if (!block)
	{
		delete block;
		block = nullptr;
	}
	if (type == LevelItemType::block)
	{
		assert(maxHealth != -1);
		block = new Block(maxHealth);
	}
	assert(type != LevelItemType::last);
}


Level::LevelItem::LevelItem(const LevelItem & other)
{
	if (!block)
	{
		delete block;
		block = nullptr;
	}
	type = other.type;
	block = other.block;
	assert(type != LevelItemType::last);
}

Level::LevelItem & Level::LevelItem::operator=(const LevelItem & other)
{
	if (!block)
	{
		delete block;
		block = nullptr;
	}
	type = other.type;
	block = other.block;
	assert(type != LevelItemType::last);
	return *this;
}

Level::LevelItem & Level::LevelItem::operator=(const LevelItemType type)
{
	if (!block)
	{
	delete block;
	block = nullptr;
	}
	this->type = type;
	if (type == LevelItemType::block || type == LevelItemType::last)
	{
		assert(false);
	}
	return *this;
}


Level::LevelItem::~LevelItem()
{
	if (!block)
	{
		delete block;
		block = nullptr;
	}
}

void Level::LevelItem::DamegeBlock()
{
	assert(!block);
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

void Level::LevelItem::Draw(sf::RenderTarget & rt, const int x, const int y)
{
	
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
