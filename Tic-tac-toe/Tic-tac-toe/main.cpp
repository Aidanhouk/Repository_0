// AI �������� ������ ��� ���� 3x3, ��� ������ ������������ - ������ ������
// ��� ����� ������ - ������

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "mainGame.h"

int main()
{
	// ����������� ���� + �������� �� ���������
	int n{ 3 };
	// ��� vs ���? 1 - player vs player, 2 - player vs AI, 3 - AI vs AI
	int p{ 2 };

	// ��������� ����
	openMenu(n, p);

	// ��������� ����
	mainGame(n, p);

	return 0;
}