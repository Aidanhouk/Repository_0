#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

// �����, ���������� �� ������� �������
class Shop
{
private:
	// ����� �������
	sf::Font *m_font;
	// ������� ����� � ������
	sf::Texture* m_towersTextures[TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1]{ nullptr };
	// �������� ������
	sf::Texture* m_coinTexture;
	// �������� ������ ���������� ��������
	sf::Texture* m_normalTexture;
	// �������� ������ ������� ��������
	sf::Texture* m_fasterTexture;
	// �������� ������ ������
	sf::Texture* m_startTexture;
	// �������� ������ �����
	sf::Texture* m_pauseTexture;
	// ����� ��������� �����/�����
	sf::RectangleShape* m_chosenTowerFrame[4];
public:
	Shop();
	~Shop();
	// ������������ ���� �������
	void drawShop(int currentWave, int maxWaveLevel, int blockType);
};