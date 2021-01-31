#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

// класс, отвечающий за область покупки
class Shop
{
private:
	// шрифты
	sf::Font *m_font1;
	sf::Font *m_font2;
	// тектуры башен и блоков
	sf::Texture* m_towersTextures[TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1]{ nullptr };
	// текстура монеты
	sf::Texture* m_coinTexture;
	// текстура иконки нормальной скорости
	sf::Texture* m_normalTexture;
	// текстура иконки быстрой скорости
	sf::Texture* m_fasterTexture;
	// текстура иконки старта
	sf::Texture* m_startTexture;
	// текстура иконки паузы
	sf::Texture* m_pauseTexture;
	// текстура окна с информацией о башне/блоке
	sf::Texture* m_infoTexture;
	// рамка выбранной башни/блока
	sf::RectangleShape* m_chosenTowerFrame[4];
public:
	Shop();
	~Shop();
	// отрисовываем весь магазин
	void drawShop(int currentWave, int maxWaveLevel, int blockType);
	// возращает индекс товара в магазине
	int returnItemNumber(int posX, int posY);
	// отрисовка информации о товаре, на который наведена мышка
	void itemInfo(int itemType);
};