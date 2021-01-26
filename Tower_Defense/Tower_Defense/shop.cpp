#include "shop.h"

#include <string>

#include "globals.h"

Shop::Shop()
{
	// скачиваем шрифт
	m_font = new sf::Font();
	(*m_font).loadFromFile("sansation.ttf");

	// создаем объект фона магазина
	m_border = new sf::RectangleShape(sf::Vector2f(W * 3, W * ROWS));
	(*m_border).move(W * COLS, 0);
	(*m_border).setFillColor(sf::Color::Black);

	// скачиваем и записываем текстуры башен
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Texture *tower{ new sf::Texture() };
		(*tower).loadFromFile("images/towers/tower" + std::to_string(i) + ".png");
		m_towersTextures[i] = tower;
	}

	// скачиваем и записываем текстуры блоков
	for (int i = 1; i < FIELD_BLOCKS_COUNT; ++i) {
		sf::Texture *block{ new sf::Texture() };
		(*block).loadFromFile("images/fieldBlocks/block" + std::to_string(i) + ".png");
		m_towersTextures[TOWERS_COUNT + i - 1] = block;
	}

	// скачиваем и записываем текстуру монеты
	m_coinTexture = new sf::Texture();
	(*m_coinTexture).loadFromFile("images/other/coin.png");

	// скачиваем и записываем текстуру иконки норм скорости
	m_normalTexture = new sf::Texture();
	(*m_normalTexture).loadFromFile("images/other/normal.png");

	// скачиваем и записываем текстуру иконки быстрой скорости
	m_fasterTexture = new sf::Texture();
	(*m_fasterTexture).loadFromFile("images/other/faster.png");

	// скачиваем и записываем текстуру иконки старта
	m_startTexture = new sf::Texture();
	(*m_startTexture).loadFromFile("images/other/start.png");

	// скачиваем и записываем текстуру иконки пазуы
	m_pauseTexture = new sf::Texture();
	(*m_pauseTexture).loadFromFile("images/other/pause.png");

	// добавляем прямоугольники для обводки выбранного объекта для покупки
	sf::RectangleShape *chosenTower1{ new sf::RectangleShape(sf::Vector2f(W, W / 10)) };
	(*chosenTower1).setFillColor(sf::Color(0, 255, 0));
	m_chosenTowerFrame[0] = chosenTower1;
	m_chosenTowerFrame[1] = chosenTower1;
	sf::RectangleShape *chosenTower2{ new sf::RectangleShape(sf::Vector2f(W / 10, W)) };
	(*chosenTower2).setFillColor(sf::Color(0, 255, 0));
	m_chosenTowerFrame[2] = chosenTower2;
	m_chosenTowerFrame[3] = chosenTower2;
}

Shop::~Shop()
{
	for (auto var : m_towersTextures) {
		if (var) {
			delete var;
		}
	}
	delete m_chosenTowerFrame[0];
	delete m_chosenTowerFrame[2];
	delete m_font;
	delete m_border;
	delete m_coinTexture;
	delete m_normalTexture;
	delete m_fasterTexture;
	delete m_startTexture;
	delete m_pauseTexture;
}

void Shop::drawShop(int currentWave, int maxWaveLevel, int blockType, sf::RenderWindow & window)
{
	// область покупки башен
	window.draw(*m_border);

	// текст с деньгами + монета
	sf::Sprite coin(*m_coinTexture);
	coin.setPosition(W * (COLS + 1), 0);
	window.draw(coin);
	sf::Text moneyText(std::to_string(money), *m_font, 40);
	moneyText.setFillColor(sf::Color::Yellow);
	moneyText.setPosition(W * (COLS + 0.1), W / 5);
	window.draw(moneyText);

	// иконка старта / паузы
	sf::Sprite pauseIcon;
	if (pause) {
		pauseIcon.setTexture(*m_startTexture);
		pauseIcon.setPosition(W * COLS + 30, W * (ROWS - 3) + 20);
	}
	else {
		pauseIcon.setTexture(*m_pauseTexture);
		pauseIcon.setPosition(W * COLS, W * (ROWS - 3));
	}
	window.draw(pauseIcon);

	// иконка скорости игры
	sf::Sprite speedIcon;
	if (gameSpeed) {
		speedIcon.setTexture(*m_normalTexture);
	}
	else {
		speedIcon.setTexture(*m_fasterTexture);
	}
	speedIcon.setPosition(W * (COLS + 1), W * (ROWS - 1));
	window.draw(speedIcon);

	// текст с номером волны
	sf::Text levelText(std::to_string(currentWave) + "/" + std::to_string(maxWaveLevel), *m_font, 37);
	levelText.setFillColor(sf::Color::Red);
	levelText.setPosition(W * COLS + 8, W * (ROWS - 1) + W / 5);
	window.draw(levelText);

	// рисуем башни, блоки и их стоимость
	bool x{ 0 };
	double y{ 0 };
	for (int i = 1; i < TOWERS_COUNT + FIELD_BLOCKS_COUNT - 1; ++i) {
		sf::Sprite block(*m_towersTextures[i]);
		block.setPosition(W * (COLS + x), W * (1 + y));
		window.draw(block);
		// узнаем цену башни/блока
		int price{ (i < TOWERS_COUNT) ? TOWERS_PRICE[i] : BLOCKS_PRICE[i - TOWERS_COUNT + 1] };
		sf::Text cost(std::to_string(price), *m_font, 30);
		if (money >= price) {
			cost.setFillColor(sf::Color::Yellow);
		}
		else {
			cost.setFillColor(sf::Color::Red);
		}
		cost.setPosition(block.getPosition().x + W * 0.3, block.getPosition().y + W);
		window.draw(cost);
		if (x) {
			y += 1.5;
			x = 0;
		}
		else {
			x = 1;
		}
	}

	// обводим выбранную башню/блок
	if (blockType) {
		int _x{ (blockType - 1) % 2 };
		int _y{ (blockType - 1) >> 1 };
		(*m_chosenTowerFrame[0]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5));
		window.draw(*m_chosenTowerFrame[0]);
		(*m_chosenTowerFrame[1]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5) + W - W / 10);
		window.draw((*m_chosenTowerFrame[1]));
		(*m_chosenTowerFrame[2]).setPosition(W * (COLS + _x), W * (1 + _y * 1.5));
		window.draw((*m_chosenTowerFrame[2]));
		(*m_chosenTowerFrame[3]).setPosition(W * (COLS + _x) + W - W / 10, W * (1 + _y * 1.5));
		window.draw((*m_chosenTowerFrame[3]));
	}
}