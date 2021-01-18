#include "missilesControl.h"

#include "consts.h"

void Missiles::drawMissiles(sf::RenderWindow & window)
{
	for (auto & var : missilesVector) {
		// ���� ���� ��� ��� ����� ��������;
		if (var->second->isAlive()) {
			// ������� �������� � ����������� �� ��������������� �����
			std::pair<int, int> coordDif{ var->second->getPositionEnemy()->getCoordinates().second - var->first.second,
				var->second->getPositionEnemy()->getCoordinates().first - var->first.first };
			// ���� ��������� ��� ��� ������� ��������� �����
			if (!(coordDif.first <= 1 && coordDif.first >= -1 && coordDif.second <= 1 && coordDif.second >= -1)) {
				return;
			}
			// �������
			sf::RectangleShape missile(sf::Vector2f(W * 1.2, 2));

			int direction{ var->second->getDirection() };
			int distance{ var->second->getDistance() };
			// ��� ������������� ������ ��������� ���������� ������������ ������, �� ������� �� ���������
			// ��������� ��� � ������� ��� ����������� �������� ��������
			distance = 45.f * (static_cast<double>(distance) / W);
			// ��� ������������� ����� ��������, ���� ���� ��������� ����������� � ����� � ���������� �� ���
			// ��������, � ������ ������� ������ ������������ ����� � ���� ����� ��� �������
			// �����, ���� ���� ��������� �� ����� �� ����� � ����������
			int diagDist = W * 1.6 + 0.9 * W * (static_cast<double>(distance) / W);
			switch (coordDif.second)
			{
			case 0:
				// ���� �� ����� ��� �� �������������� �����
				switch (coordDif.first)
				{
				case -1:
					// ���� �� 1 ������ �����
					// � ����������� �� �����������, ������ ���� ��������
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
					// ���� �� 1 ������ ������
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
				// ���� ����
				switch (coordDif.first)
				{
				case 0:
					// ���� �� ���� ������ ����
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
					// ���� � ����� ������� ����
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
					// ���� � ������ ������� ����
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
				// ���� ����
				switch (coordDif.first)
				{
				case 0:
					// ���� �� 1 ������ ����
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
					// ���� � ����� ������ ����
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
					// ���� � ������ ������ ����
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

			// ���� ������������ ��������� �����
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