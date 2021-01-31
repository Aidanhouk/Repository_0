#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class BlockOnField;

// класс, отвечающий за контроль блоков на поле
class BlocksControl
{
private:
	// все блоки на поле
	std::vector<BlockOnField*> m_blocks;
	// тектуры блоков
	sf::Texture* m_blocksTextures[FIELD_BLOCKS_COUNT]{ nullptr };
public:
	BlocksControl();
	~BlocksControl();

	// поставить блок на дорогу
	bool placeBlockOnField(int y, int x, int blockType);
	// отрисовать все блоки
	void drawAllBlocks();
	// удалить блок
	void removeBlock(BlockOnField * block);
	// удалить блок с поля + вернуть половину его стоимости
	int deleteBlock(int i, int j);
};