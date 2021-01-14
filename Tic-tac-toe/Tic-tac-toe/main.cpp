// AI �������� ������ ��� ���� 3x3, ��� ������ ������������ - ������ ������
// ��� ����� ������ - ������

#include "menu.h"
#include "mainGame.h"
#include "results.h"

int main()
{
	// ����������� ���� + �������� �� ���������
	int n{ 3 };
	// ��� vs ���? 1 - player vs player, 2 - player vs AI, 3 - AI vs AI
	int p{ 2 };
	// ���� ������� ��������� ����
	int res{ 0 };
	// ���� 1, ���� ���������������
	bool gameContinues{ 1 };

	while (gameContinues) {
		// ������ ��� ������������� �������� �� ���������
		n = 3, p = 2, res = 0;

		// ��������� ����
		openMenu(n, p);

		// ��������� ����
		mainGame(n, p, res);

		// �����������
		results(res, p, gameContinues);
	}

	return 0;
}