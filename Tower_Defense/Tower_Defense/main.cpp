// � ��������� consts.h ����� ��������� ��������� ���� � �������
// � ����� field.cpp � ������� makeRoad() ����� ������� ����� ������ �� �����������

void menu(int &level);
void mainGame(int &result, int level, int &waveLevel);
void result(int result, int waveLevel, bool &playAgain);

int main()
{
	// ���� ������� ��������� ���� 0 - ������ ����, 1 - ������ ����, 2 - ��������
	int res{ 0 };
	// ����� ������� ������?
	int level{ 1 };
	// �� ����� ����� ����������� ����?
	int waveLevel{ 0 };
	// ������ �����?
	bool playAgain{ 1 };

	while (playAgain) {
		// ���������� ��� ���������
		res = 0; level = 1; waveLevel = 0;

		// ����� ������
		menu(level);

		// �������� ����
		mainGame(res, level, waveLevel);

		// ���������
		result(res, waveLevel, playAgain);
	}

	return 0;
}