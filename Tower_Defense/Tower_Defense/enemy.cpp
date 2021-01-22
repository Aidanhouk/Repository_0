#include "enemy.h"

Enemy::Enemy(int type, sf::Texture * enemyTextures[ENEMIES_COUNT])
	: m_type{ type }, m_enemyTexture{ enemyTextures[type] }
{
	m_hp = ENEMIES_HP[type];
	m_coins = ENEMIES_COINS[type];
	m_speed = ENEMIES_SPEED[type];
}

void Enemy::setDirection(RoadCell * currentPosition)
{
	// вычислим разницу между координатами текущей и след ячейки
	std::pair<int, int> coordCurrentPos{ currentPosition->getCoordinates() };
	std::pair<int, int> coordNextPos{ currentPosition->getNextCell()->getCoordinates() };
	std::pair<int, int> coordDifference{ coordNextPos.first - coordCurrentPos.first, coordNextPos.second - coordCurrentPos.second };
	// можно и не создавать доп переменные, но будет уж слишком много кода в одном выражении
	switch (coordDifference.first)
	{
	case -1:
		m_direction = 1;
		break;
	case 1:
		m_direction = 3;
		break;
	case 0:
		switch (coordDifference.second)
		{
		case -1:
			m_direction = 4;
			break;
		case 1:
			m_direction = 2;
			break;
		}
		break;
	}
}

void Enemy::changePosition()
{
	m_distance = 0;
	// удаляем с текущей клетки врага
	m_position->removeEnemyFromCell(this);
	// переходим на следующую ячейку
	m_position = m_position->getNextCell();
	// добавляем в нее текущего врага
	m_position->setEnemyOnCell(this);
}

void Enemy::drawEnemy(sf::RenderWindow &window)
{
	//sf::Sprite enemy;
	//enemy.setTexture(*m_enemyTexture);
	sf::CircleShape enemy(30, m_type + 2);
	switch (m_direction)
	{
	case 1:
		enemy.setPosition((float)(W) * m_position->getCoordinates().second + 10, (float)(W) * m_position->getCoordinates().first + 10 - m_distance);
		break;
	case 2:
		enemy.setPosition((float)(W) * m_position->getCoordinates().second + 10 + m_distance, (float)(W) * m_position->getCoordinates().first + 10);
		break;
	case 3:
		enemy.setPosition((float)(W) * m_position->getCoordinates().second + 10, (float)(W) * m_position->getCoordinates().first + 10 + m_distance);
		break;
	case 4:
		enemy.setPosition((float)(W) * m_position->getCoordinates().second + 10 - m_distance, (float)(W) * m_position->getCoordinates().first + 10);
		break;
	}
	switch (m_type)
	{
	case 1:
		enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		enemy.setFillColor(sf::Color::Green);
		break;
	case 3:
		enemy.setFillColor(sf::Color::Cyan);
		break;
	case 4:
		enemy.setFillColor(sf::Color::Black);
		break;
	}
	window.draw(enemy);
}

void Enemy::drawHPBar(sf::RenderWindow & window)
{
	sf::RectangleShape hpBarRed(sf::Vector2f(W * 0.5, 4));
	hpBarRed.setFillColor(sf::Color::Red);
	sf::RectangleShape hpBarGreen(sf::Vector2f(W * 0.5 * ((float)m_hp / ENEMIES_HP[m_type]), 4));
	hpBarGreen.setFillColor(sf::Color::Green);
	switch (m_direction)
	{
	case 1:
		hpBarRed.setPosition((float)(W)* m_position->getCoordinates().second + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 - m_distance + W * 0.75);
		hpBarGreen.setPosition((float)(W)* m_position->getCoordinates().second + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 - m_distance + W * 0.75);
		break;
	case 2:
		hpBarRed.setPosition((float)(W)* m_position->getCoordinates().second + m_distance + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + W * 0.75);
		hpBarGreen.setPosition((float)(W)* m_position->getCoordinates().second + m_distance + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + W * 0.75);
		break;
	case 3:
		hpBarRed.setPosition((float)(W)* m_position->getCoordinates().second + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + m_distance + W * 0.75);
		hpBarGreen.setPosition((float)(W)* m_position->getCoordinates().second + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + m_distance + W * 0.75);
		break;
	case 4:
		hpBarRed.setPosition((float)(W)* m_position->getCoordinates().second - m_distance + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + W * 0.75);
		hpBarGreen.setPosition((float)(W)* m_position->getCoordinates().second - m_distance + W * 0.25, (float)(W)* m_position->getCoordinates().first + 10 + W * 0.75);
		break;
	}
	window.draw(hpBarRed);
	window.draw(hpBarGreen);
}

void Enemy::drawShot(sf::RenderWindow & window)
{
	sf::CircleShape wound(30, m_type + 2);
	switch (m_direction)
	{
	case 1:
		wound.setPosition((float)(W)* m_position->getCoordinates().second + 10, (float)(W)* m_position->getCoordinates().first + 10 - m_distance);
		break;
	case 2:
		wound.setPosition((float)(W)* m_position->getCoordinates().second + 10 + m_distance, (float)(W)* m_position->getCoordinates().first + 10);
		break;
	case 3:
		wound.setPosition((float)(W)* m_position->getCoordinates().second + 10, (float)(W)* m_position->getCoordinates().first + 10 + m_distance);
		break;
	case 4:
		wound.setPosition((float)(W)* m_position->getCoordinates().second + 10 - m_distance, (float)(W)* m_position->getCoordinates().first + 10);
		break;
	}
	wound.setFillColor(sf::Color::Red);
	window.draw(wound);
}