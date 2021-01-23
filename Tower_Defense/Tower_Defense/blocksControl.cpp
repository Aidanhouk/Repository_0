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
	RoadCell * clickedCell{ (*m_field).getStartPos() };
	// ������� ������ ��� ������ �� ������
	while (clickedCell->getCoordinates().first != y || clickedCell->getCoordinates().second != x) {
		clickedCell = clickedCell->getNextCell();
	}
	if (clickedCell == (*m_field).getFinishPos()) {
		return 0;
	}
	// �������� ��� "�����������", ����� ���� ��� ���� ������ � ������ �� ������������
	RoadCell *cell2{ nullptr };
	if (clickedCell->getNextCell()) {
		cell2 = clickedCell->getNextCell();
		while (cell2->getCoordinates().first != y || cell2->getCoordinates().second != x) {
			if (!cell2->getNextCell()) {
				break;
			}
			cell2 = cell2->getNextCell();
		}
	}
	// ��������� ��� � ����������
	bool cell2Found{ 0 };
	if (cell2) {
		if (cell2->getCoordinates().first == y && cell2->getCoordinates().second == x) {
			cell2Found = 1;
		}
	}
	// ���� �� ������� � ���������� ������ ��� ������
	if (clickedCell->isCellClear() && clickedCell->getPrevCell()->isCellClear()) {
		// ���� ����� �������� � �� ������ �������
		if (cell2Found) {
			if (!cell2->isCellClear() || !cell2->getPrevCell()->isCellClear()) {
				return 0;
			}
		}
		BlockOnField *block{ new BlockOnField(blockType, m_blocksTextures, this) };
		block->addCell(clickedCell);
		clickedCell->setBlockOnCell(block);
		// ���� ������� ������ ������������ ������
		if (cell2Found) {
			block->addCell2(cell2);
			cell2->setBlockOnCell(block);
		}
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
	// ���� ���� 2 ������, �� ������� ��������� ����
	if (block->getCell2()) {
		block->getCell2()->setBlockOnCell(nullptr);
	}
	m_blocks.erase(std::find(m_blocks.begin(), m_blocks.end(), block));
}
