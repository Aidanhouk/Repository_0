// ����������� AI �������� ������ ��� ���� 3x3
// ��� ������ ������������ �������������� �������� �� �����, ������� ����� ���������,
// ����� �������� ��� �� ���� �������� ����������, ���� ����� ����� ���, �� ��������� �� ��������� ������
// ��� ����� ������ - ������

#include "globals.h"
#include "menu.h"
#include "mainGame.h"
#include "results.h"

// ����������� ����
int n;
// ��� ������ ����
int _WhoVsWho;
// ��������� ����
int gameResult;
// ���� ����
Field * field;
// ���� ���� 
sf::RenderWindow *window;

// ���� 1, ���� ���������������
bool gameContinues{ 1 };

int main()
{
	while (gameContinues) {
		// ������������� �������� �� ���������
		n = 3, _WhoVsWho = 2, gameResult = -1;

		// ��������� ����
		menu();

		// ��������� ����
		mainGame();

		// �����������
		results(gameContinues);
	}

	return 0;
}