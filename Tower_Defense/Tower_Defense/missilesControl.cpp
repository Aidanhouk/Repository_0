#include "missilesControl.h"

#include "consts.h"

void Missiles::drawMissiles(sf::RenderWindow & window)
{
	for (auto & var : missilesVector) {

		// �������
		sf::RectangleShape missile(sf::Vector2f(W * 0.6, 8));
		missile.move((float)(W) * var->first.second + (float)(W) * (float)(0.5), (float)(W) * var->first.first + (float)(W) * (float)(0.5));

		// ������� �������� � ����������� �� ��������������� �����
		std::pair<int, int> coordDif{ var->second->getCoordinates().second - var->first.second,
			var->second->getCoordinates().first - var->first.first };
		switch (coordDif.second)
		{
		case 0:
			// ���� �� ����� ��� �� �������������� �����
			switch (coordDif.first)
			{
			case -1:
				// ���� �� 1 ������ �����
				missile.rotate(180);
				break;
			case 1:
				// ���� �� 1 ������ ������
				missile.rotate(0);
				break;
			}
			break;
		case -1:
			// ���� ����
			switch (coordDif.first)
			{
			case 0:
				// ���� �� ���� ������ ����
				missile.rotate(-90);
				break;
			case -1:
				// ���� � ����� ������� ����
				missile.rotate(-135);
				break;
			case 1:
				// ���� � ������ ������� ����
				missile.rotate(-45);
				break;
			}
			break;
		case 1:
			// ���� ����
			switch (coordDif.first)
			{
			case 0:
				// ���� �� 1 ������ ����
				missile.rotate(90);
				break;
			case -1:
				// ���� � ����� ������ ����
				missile.rotate(135);
				break;
			case 1:
				// ���� � ������ ������ ����
				missile.rotate(45);
				break;
			}
			break;
		}
		missile.setFillColor(sf::Color::Black);
		window.draw(missile);

		// ���� ������������ ��������� �����, ���� �� ��� ���
		if (var->second->getEnemyOnCell()) {
			var->second->getEnemyOnCell()->drawShot(window);
		}
	}
}

void Missiles::addMissile(std::pair<std::pair<int, int>, RoadCell*> *missile)
{
	missilesVector.push_back(missile);
}

void Missiles::deleteMissiles()
{
	for (auto & var : missilesVector) {
		delete var;
	}
	missilesVector.clear();
}