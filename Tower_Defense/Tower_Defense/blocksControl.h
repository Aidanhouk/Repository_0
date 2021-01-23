#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Field;
class BlockOnField;

class BlocksControl
{
private:
	// ��� ����� �� ����
	std::vector<BlockOnField*> m_blocks;
	// ������� ������
	sf::Texture* m_blocksTextures[FIELD_BLOCKS_COUNT]{ nullptr };
	// ����
	Field * m_field;
public:
	BlocksControl(Field & field);
	~BlocksControl();

	// ��������� ���� �� ������
	bool placeBlockOnField(int y, int x, int blockType);
	// ���������� ��� �����
	void drawAllBlocks(sf::RenderWindow &window);
	// ������� ����
	void removeBlock(BlockOnField * block);
};