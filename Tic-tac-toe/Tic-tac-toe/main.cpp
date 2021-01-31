// ����������� AI �������� ������ ��� ���� 3x3
// ��� ������ ������������ �������������� �������� �� �����, ������� ����� ���������,
// ����� �������� ��� �� ���� �������� ����������, ���� ����� ����� ���, �� ��������� �� ��������� ������
// ��� ����� ������ - ������

#include "globals.h"
#include "menu.h"
#include "mainGame.h"
#include "results.h"

// ����������� ���� + �������� �� ���������
int n;
// ��� vs ���? 1 - player vs player, 2 - player vs AI, 3 - AI vs AI
int p;
// ���� ������� ��������� ����
int res;
// ���� 1, ���� ���������������
bool gameContinues{ 1 };

int main()
{
	while (gameContinues) {
		// ������������� �������� �� ���������
		n = 3, p = 2, res = -1;

		// ��������� ����
		menu();

		// ��������� ����
		mainGame();

		// �����������
		results(gameContinues);
	}

	return 0;
}