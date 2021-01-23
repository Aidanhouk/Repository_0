#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Field;
class BlockOnField;

class BlocksControl
{
private:
	// все блоки на поле
	std::vector<BlockOnField*> m_blocks;
	// тектуры блоков
	sf::Texture* m_blocksTextures[FIELD_BLOCKS_COUNT]{ nullptr };
	// поле
	Field * m_field;
public:
	BlocksControl(Field & field);
	~BlocksControl();

	// поставить блок на дорогу
	bool placeBlockOnField(int y, int x, int blockType);
	// отрисовать все блоки
	void drawAllBlocks(sf::RenderWindow &window);
	// удалить блок
	void removeBlock(BlockOnField * block);
};