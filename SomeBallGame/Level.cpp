#include "Level.h"

Level::Level(const int levelWidth, const int levelHeight)
	:
	levelWidth(levelWidth),
	levelHeight(levelHeight)
{
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
