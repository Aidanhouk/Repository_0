#include "missilesControl.h"

#include "consts.h"

void Missiles::drawMissiles(sf::RenderWindow & window)
{
	for (auto & var : missilesVector) {
		// если враг еще жив после выстрела;
		if (var->second->isAlive()) {
			// поворот выстрела в зависимости от местонахождения врага
			std::pair<int, int> coordDif{ var->second->getPositionEnemy()->getCoordinates().second - var->first.second,
				var->second->getPositionEnemy()->getCoordinates().first - var->first.first };
			// если противник уже вне радиуса поражения башни
			if (!(coordDif.first <= 1 && coordDif.first >= -1 && coordDif.second <= 1 && coordDif.second >= -1)) {
				return;
			}
			// выстрел
			sf::RectangleShape missile(sf::Vector2f(W * 1.2, 2));

			int direction{ var->second->getDirection() };
			int distance{ var->second->getDistance() };
			// тут высчитывается точное положение противника относительно клетки, на которой он находится
			// переводим это в градусы для дальнейшего поворота выстрела
			distance = 45.f * (static_cast<double>(distance) / W);
			// тут высчитывается длина выстрела, если враг находится диагонально к башне и отдаляется от нее
			// например, в правой верхней клетке относительно башни и идет вверх или направо
			// также, если враг находится по бокам от башни и отдаляется
			int diagDist = W * 1.6 + 0.9 * W * (static_cast<double>(distance) / W);
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
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
						missile.rotate(180 + distance);
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
						missile.rotate(180 - distance);
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(diagDist * 0.8, 2));
						break;
					}
					break;
				case 1:
					// враг на 1 клетку правее
					switch (direction)
					{
					case 1:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
						missile.rotate(0 - distance);
						break;
					case 2:
						missile = sf::RectangleShape(sf::Vector2f(diagDist * 0.8, 2));
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
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
						missile = sf::RectangleShape(sf::Vector2f(diagDist * 0.8, 2));
						break;
					case 2:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
						missile.rotate(-90 + distance);
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
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
						missile.rotate(-135 + (distance / 2.5));
						break;
					case 2:
						missile.rotate(-135 + distance);
						break;
					case 3:
						missile.rotate(-135 - distance);
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-135 - (distance / 2.5));
						break;
					}
					break;
				case 1:
					// враг в правом верхнем углу
					switch (direction)
					{
					case 1:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-45 - (distance / 2.5));
						break;
					case 2:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(-45 + (distance / 2.5));
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
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
						missile.rotate(90 - distance);
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(diagDist * 0.8, 2));
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(W * 1.1, 2));
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
						missile.rotate(135 - (distance / 2.5));
						break;
					case 4:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(135 + (distance / 2.5));
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
						missile.rotate(45 - (distance / 2.5));
						break;
					case 3:
						missile = sf::RectangleShape(sf::Vector2f(diagDist, 2));
						missile.rotate(45 + (distance / 2.5));
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

			// враг отрисовывает получение урона
			var->second->drawShot(window);
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