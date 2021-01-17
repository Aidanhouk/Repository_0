#include "missilesControl.h"

#include "consts.h"

void Missiles::drawMissiles(sf::RenderWindow & window)
{
	for (auto & var : missilesVector) {
		// если врага еще жив после выстрела
		if (var->second->getEnemyOnCell()) {
			// выстрел
			sf::RectangleShape missile(sf::Vector2f(W * 1.2, 2));

			// поворот выстрела в зависимости от местонахождения врага
			std::pair<int, int> coordDif{ var->second->getCoordinates().second - var->first.second,
				var->second->getCoordinates().first - var->first.first };
			int direction{ var->second->getEnemyOnCell()->getDirection() };
			int distance{ var->second->getEnemyOnCell()->getDistance() };
			// тут высчитывается точное положение противника относительно клетки, на которой он находится
			// переводим это в градусы для дальнейшего поворота выстрела
			distance = 45.f * (static_cast<double>(distance) / W);
			// тут высчитывается длина выстрела, если враг находится диагонально к башне и отдаляется от нее
			int diagDist = W * 1.7 + 0.8 * W * (static_cast<double>(distance) / W);
			switch (coordDif.second)
			{
			case 0:
				// враг на одной той же горизонтальной линии
				switch (coordDif.first)
				{
				case -1:
					// враг на 1 клетку левее
					// в зависимости от направления, меняем угол выстрела
					switch (direction)
					{
					case 1:
						missile.rotate(180 + distance);
						break;
					case 3:
						missile.rotate(180 - distance);
						break;
					case 4:
						break;
					}
					break;
				case 1:
					// враг на 1 клетку правее
					switch (direction)
					{
					case 1:
						missile.rotate(0 - distance);
						break;
					case 2:
						break;
					case 3:
						missile.rotate(0 + distance);
						break;
					}
					break;
				}
				break;
			case -1:
				// враг выше
				switch (coordDif.first)
				{
				case 0:
					// враг на одну клетку выше
					switch (direction)
					{
					case 1:
						break;
					case 2:
						missile.rotate(-90 + distance);
						break;
					case 4:
						missile.rotate(-90 - distance);
						break;
					}
					break;
				case -1:
					// враг в левом верхнем углу
					switch (direction)
					{
					case 1:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-135 + (distance >> 1));
						break;
					case 2:
						missile.rotate(-135 + distance);
						break;
					case 3:
						missile.rotate(-135 - distance);
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-135 - (distance >> 1));
						break;
					}
					break;
				case 1:
					// враг в правом верхнем углу
					switch (direction)
					{
					case 1:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-45 - (distance >> 1));
						break;
					case 2:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-45 + (distance >> 1));
						break;
					case 3:
						missile.rotate(-45 + distance);
						break;
					case 4:
						missile.rotate(-45 - distance);
						break;
					}
					break;
				}
				break;
			case 1:
				// враг ниже
				switch (coordDif.first)
				{
				case 0:
					// враг на 1 клетку ниже
					switch (direction)
					{
					case 2:
						missile.rotate(90 - distance);
						break;
					case 3:
						break;
					case 4:
						missile.rotate(90 + distance);
						break;
					}
					break;
				case -1:
					// враг в левом нижнем углу
					switch (direction)
					{
					case 1:
						missile.rotate(135 + distance);
						break;
					case 2:
						missile.rotate(135 - distance);
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(135 - (distance >> 1));
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(135 + (distance >> 1));
						break;
					}
					break;
				case 1:
					// враг в правом нижнем углу
					switch (direction)
					{
					case 1:
						missile.rotate(45 - distance);
						break;
					case 2:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(45 - (distance >> 1));
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(45 + (distance >> 1));
						break;
					case 4:
						missile.rotate(45 + distance);
						break;
					}
					break;
				}
				break;
			}
			missile.move(W * var->first.second + W * 0.5, W* var->first.first + W * 0.5);
			missile.setFillColor(sf::Color::White);
			window.draw(missile);

			// враг отрисовывает получение урона, если он еще жив
			var->second->getEnemyOnCell()->drawShot(window);
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