#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

// �����, ���������� �� ������� �������
class Shop
{
private:
	// ����� �������
	sf::Font *m_font;
	// ��� ��������
	sf::RectangleShape *m_border;
	// ������� ����� � ������
	sf::Texture* m_towersTextures[TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1]{ nullptr };
	// ����� ��������� �����/�����
	sf::RectangleShape* m_chosenTowerFrame[4];
public:
	Shop();
	~Shop();
	// ������������ ���� �������
	void drawShop(int level, int money, int type, sf::RenderWindow &window);
};