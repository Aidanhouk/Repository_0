#include "blocksControl.h"

#include "field.h"
#include "roadCell.h"
#include "blockOnField.h"

BlocksControl::BlocksControl(Field & field)
	: m_field{&field}
{
	// ��������� � ���������� �������� ������
	for (int i = 1; i < FIELD_BLOCKS_COUNT; ++i) {
		sf::Texture *block{ new sf::Texture() };
		(*block).loadFromFile("images/fieldBlocks/block" + std::to_string(i) + ".png");
		m_blocksTextures[i] = block;
	}
}

BlocksControl::~BlocksControl()
{
	for (auto & var : m_blocks) {
		if (var) {
			delete var;
		}
	}
	for (auto var : m_blocksTextures) {
		if (var) {
			delete var;
		}
	}
}

bool BlocksControl::placeBlockOnField(int y, int x, int blockType)
{
	RoadCell * clickedCell{ (*m_field).getFinishPos() };
	// ������� ������ ��� ������ �� ������
	while (clickedCell->getCoordinates().first != y || clickedCell->getCoordinates().second != x) {
		clickedCell = clickedCell->getPrevCell();
	}
	// ���� �� ������� � ���������� ������ ��� ������
	if (clickedCell->isCellClear() && clickedCell->getPrevCell()->isCellClear()) {
		BlockOnField *block{ new BlockOnField(blockType, m_blocksTextures, this) };
		block->setCell(clickedCell);
		clickedCell->setBlockOnCell(block);
		m_blocks.push_back(block);
		return 1;
	}
	else {
		return 0;
	}
}

void BlocksControl::drawAllBlocks(sf::RenderWindow & window)
{
	for (auto & var : m_blocks) {
		var->drawBlock(window);
		if (var->getType() == 2) {
			var->drawHPBar(window);
		}
	}
}

void BlocksControl::removeBlock(BlockOnField * block)
{
	// ������� ���� � ������, �� ������� �� ���������
	m_field->getCell(block->getCell()->getCoordinates().first, block->getCell()->getCoordinates().second) = 1;
	block->getCell()->setBlockOnCell(nullptr);
	m_blocks.erase(std::find(m_blocks.begin(), m_blocks.end(), block));
}
