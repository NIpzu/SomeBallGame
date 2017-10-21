#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Level
{
public:
	Level(const int levelWidth, const int levelHeight);
	int GetWidth();
	int GetHeight();
	void Draw(sf::RenderTarget& rt);
private:
	const int levelWidth;
	const int levelHeight;



	class LevelItem
	{
	public:
//		LevelItem();
//		~LevelItem();

	private:

	};


	class Block
		{
		public:
		//	Block();
		//	void Draw(sf::RenderTarget& rt);
		private:
		};


	std::vector<LevelItem*> LevelGrid;
};
