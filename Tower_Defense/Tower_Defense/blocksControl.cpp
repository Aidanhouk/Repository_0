#include "blocksControl.h"

#include "globals.h"
#include "field.h"
#include "roadCell.h"
#include "blockOnField.h"

BlocksControl::BlocksControl()
{
	// скачиваем и записываем текстуры блоков
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
	RoadCell * clickedCell{ (*field).getStartPos() };
	// находим нужную нам клетку на дороге
	while (clickedCell->getCoordinates().first != y || clickedCell->getCoordinates().second != x) {
		clickedCell = clickedCell->getNextCell();
	}
	if (clickedCell == (*field).getFinishPos()) {
		return 0;
	}
	// возможно это "перекресток", тогда ищем еще одну клетку с такими же координатами
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
	// фиксируем это в переменной
	bool cell2Found{ 0 };
	if (cell2) {
		if (cell2->getCoordinates().first == y && cell2->getCoordinates().second == x) {
			cell2Found = 1;
		}
	}
	// если на текущей и предыдущей клетке нет врагов
	if (clickedCell->isCellClear() && clickedCell->getPrevCell()->isCellClear()) {
		// тоже самое проверям и со второй клеткой
		if (cell2Found) {
			if (!cell2->isCellClear() || !cell2->getPrevCell()->isCellClear()) {
				return 0;
			}
		}
		BlockOnField *block{ new BlockOnField(blockType, m_blocksTextures, this) };
		block->addCell(clickedCell);
		clickedCell->setBlockOnCell(block);
		// если нашлась вторая перекрестная клетка
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

void BlocksControl::drawAllBlocks()
{
	for (auto & var : m_blocks) {
		var->drawBlock();
		if (var->getType() == 2) {
			var->drawHPBar();
		}
	}
}

void BlocksControl::removeBlock(BlockOnField * block)
{
	// удаляем блок с клетки, на которой он находится
	field->setCellValue(block->getCell()->getCoordinates().first, block->getCell()->getCoordinates().second, 1);
	block->getCell()->setBlockOnCell(nullptr);
	// если есть 2 клетка, на которой находится блок
	if (block->getCell2()) {
		block->getCell2()->setBlockOnCell(nullptr);
	}
	m_blocks.erase(std::find(m_blocks.begin(), m_blocks.end(), block));
}

int BlocksControl::deleteBlock(int i, int j)
{
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it) {
		if ((*it)->getCell()->getCoordinates().first == i && (*it)->getCell()->getCoordinates().second == j) {
			if ((*it)->getCell2()) {
				(*it)->getCell2()->setBlockOnCell(nullptr);
			}
			(*it)->getCell()->setBlockOnCell(nullptr);
			int blockPrice;
			switch ((*it)->getType())
			{
			case 1:
				blockPrice = BLOCKS_PRICE[1];
				break;
			case 2:
				blockPrice = (double)(*it)->getHP() / STOP_BLOCK_HP * BLOCKS_PRICE[2];
				break;
			default:
				break;
			}
			m_blocks.erase(it);
			return blockPrice >> 1;
		}
	}
}
