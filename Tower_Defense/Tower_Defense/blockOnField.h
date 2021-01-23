#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class RoadCell;
class BlocksControl;

class BlockOnField
{
private:
	// ��� �����
	int m_type;
	// �������� �����
	int m_hp;
	// ��������� �� ������� �����
	sf::Texture * m_blockTexture;
	// ������ ������, �� ������� ����� ����
	RoadCell * m_roadCell;
	// �������� �� ������, �������������� �����
	BlocksControl * m_blocksControl;
public:
	BlockOnField(int type, sf::Texture * blocksTextures[FIELD_BLOCKS_COUNT], BlocksControl * blocksControl);
	~BlockOnField() {}

	// ��������� �����
	void drawBlock(sf::RenderWindow & window);
	// ��������� �����
	void getDamage(int dmg);
	// ��������� ����� ��������
	void drawHPBar(sf::RenderWindow &window);

	RoadCell * getCell() { return m_roadCell; }
	void setCell(RoadCell * cell) { m_roadCell = cell; }
	int getType() const { return m_type; }
};