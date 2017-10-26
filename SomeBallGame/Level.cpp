#include "Level.h"

Level::Level()
	:
	levelWidth(Constants::LevelWidth),
	levelHeight(Constants::LevelHeight),
	blockWidth(Constants::BlockWidth),
	blockHeight(Constants::BlockHeight),
	blockShape(sf::Vector2f(float(Constants::BlockWidth) - (float(Constants::BlockWidth) / 10.0f), float(Constants::BlockHeight) - (float(Constants::BlockWidth) / 10.0f))),
	rng(rd()),
	Rand(0, static_cast<int>(LevelItemType::block)),
	extraBallShape(Constants::PowerUpRadius, int(Constants::PowerUpRadius) * 4)
{
	blockShape.setFillColor(sf::Color::Black);
	blockShape.setOutlineColor(sf::Color::White);
	blockShape.setOutlineThickness((float(Constants::BlockWidth) / 40.0f));
	extraBallShape.setOrigin(Constants::PowerUpRadius, Constants::PowerUpRadius);
	extraBallShape.setFillColor(sf::Color::Red);
	nGridItems = levelWidth * levelHeight;
	blockShape.setOrigin(-(float(Constants::BlockWidth) / 20.0f), -(float(Constants::BlockWidth) / 20.0f));
	LevelGrid.resize(levelWidth * levelHeight);
	for (int i = 0; i < nGridItems; i++)
	{
		LevelGrid[i] = new LevelItem(LevelItemType::empty);
	}
}

Level::~Level()
{
	for (int i = 0; i < nGridItems; i++)
	{
		delete LevelGrid[i];
		LevelGrid[i] = nullptr;
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
		switch (LevelGrid[i]->GetType())
		{
		case LevelItemType::block:
			blockShape.setPosition(float(x) * blockWidth, float(y) * blockHeight);
			rt.draw(blockShape);
			break;
		case LevelItemType::extraball:
			extraBallShape.setPosition((float(x) + 0.5f) * blockWidth, (float(y) + 0.5f) * blockHeight);
			rt.draw(extraBallShape);
			break;
		default:
			break;
		}
	}
}

bool Level::MoveAndAdd()
{
	CreateNewItems();
	return Move();
}

Level::LevelItemType Level::GetType(const int x, const int y) const
{
	if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight)
	{
		return LevelItemType::empty;
	}
	return LevelGrid[y * levelWidth + x]->GetType();
}

void Level::Hit(const int x, const int y)
{
	switch (LevelGrid[y * levelWidth + x]->GetType())
	{
	case LevelItemType::block:
		LevelGrid[y * levelWidth + x]->DamageBlock();
		break;
	case LevelItemType::extraball:
		*LevelGrid[y * levelWidth + x] = LevelItemType::empty;
		break;
	default:
		break;
	}
}

bool Level::Move()
{	
	
	for (int y = levelHeight - 1; y > 0; y--)
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

		LevelGrid[x] = new LevelItem(static_cast<LevelItemType>(Rand(rng)),score);
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
}

Level::LevelItem::LevelItem(const LevelItemType type)
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
		assert(false);
	}
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
	if (type == LevelItemType::block)
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

void Level::LevelItem::DamageBlock()
{
	assert(block);
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
