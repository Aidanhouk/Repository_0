#include "blockOnField.h"

#include "globals.h"
#include "roadCell.h"
#include "blocksControl.h"

BlockOnField::BlockOnField(int type, sf::Texture * blocksTextures[FIELD_BLOCKS_COUNT], BlocksControl * blocksControl)
	: m_type(type), m_blockTexture{ blocksTextures[type] }, m_blocksControl{ blocksControl }
{
	switch (type)
	{
	case 2:
		m_hp = STOP_BLOCK_HP;
		break;
	default:
		m_hp = 1;
		break;
	}
}

void BlockOnField::drawBlock()
{
	sf::Sprite block(*m_blockTexture);
	block.setPosition(W * m_roadCells[0]->getCoordinates().second, W * m_roadCells[0]->getCoordinates().first);
	(*window).draw(block);
}

void BlockOnField::getDamage(int dmg)
{
	m_hp -= dmg;
	if (m_hp <= 0) {
		m_blocksControl->removeBlock(this);
	}
}

void BlockOnField::drawHPBar()
{
	if (m_hp != STOP_BLOCK_HP) {
		sf::RectangleShape hpBarRed(sf::Vector2f(W * 0.5, 4));
		hpBarRed.setFillColor(sf::Color::Red);
		sf::RectangleShape hpBarGreen(sf::Vector2f(W * 0.5 * ((float)m_hp / STOP_BLOCK_HP), 4));
		hpBarGreen.setFillColor(sf::Color::Green);
		hpBarRed.setPosition(W * m_roadCells[0]->getCoordinates().second + W * 0.25, W * m_roadCells[0]->getCoordinates().first + 10 + W * 0.75);
		hpBarGreen.setPosition(W * m_roadCells[0]->getCoordinates().second + W * 0.25, W * m_roadCells[0]->getCoordinates().first + 10 + W * 0.75);
		(*window).draw(hpBarRed);
		(*window).draw(hpBarGreen);
	}
}