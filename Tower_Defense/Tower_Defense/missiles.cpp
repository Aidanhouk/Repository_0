#include "missiles.h"

#include "consts.h"
#include "globals.h"
#include "enemy.h"
#include "tower.h"
#include "roadCell.h"

void Missiles::drawMissiles()
{
	for (auto & var : missilesVector) {
		// если враг еще жив после выстрела;
		if (var->second->getIsAlive()) {
			// далее вычисляем точную длину и угол выстрела
			std::pair<int, int> coordDif{ var->second->getPositionEnemy()->getCoordinates().second - var->first->getPosition().second,
				var->second->getPositionEnemy()->getCoordinates().first - var->first->getPosition().first };
			int direction{ var->second->getDirection() };
			double distance{ var->second->getDistance() };
			int xDirection;
			int yDirection;
			switch (direction)
			{
			case 1:
				xDirection = 0;
				yDirection = -1;
				break;
			case 2:
				xDirection = 1;
				yDirection = 0;
				break;
			case 3:
				xDirection = 0;
				yDirection = 1;
				break;
			case 4:
				xDirection = -1;
				yDirection = 0;
				break;
			}
			// дистанция до цели по оси x
			double xVector{ coordDif.first * W + xDirection * distance };
			// дистанция до цели по оси y
			double yVector{ coordDif.second * W + yDirection * distance };
			// длина выстрела
			double missileLength{ sqrt(pow(xVector, 2) + pow(yVector, 2)) };
			// угол выстрела
			double angle{ acos(xVector / missileLength) * 180.0 / 3.14159265 };
			if (yVector < 0) { angle = -angle; }

			sf::RectangleShape missile(sf::Vector2f(missileLength, 2));
			missile.rotate(angle);
			missile.move(W * var->first->getPosition().second + W * 0.5, W * var->first->getPosition().first + W * 0.5);
			// красим выстрел в цвет башни
			switch (var->first->getTowerType())
			{
			case 1:
			case 2:
				missile.setFillColor(sf::Color::White);
				break;
			case 3:
				missile.setFillColor(sf::Color::Black);
				break;
			case 4:
				missile.setFillColor(sf::Color::Yellow);
				break;
			case 5:
				missile.setFillColor(sf::Color::Blue);
				break;
			case 6:
				missile.setFillColor(sf::Color::Green);
				break;
			}
			(*window).draw(missile);
		}
	}
}

void Missiles::deleteMissiles()
{
	for (auto & var : missilesVector) {
		delete var;
	}
	missilesVector.clear();
}