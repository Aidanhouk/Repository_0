// � ��������� consts.h ����� ��������� ��������� ���� � �������
// � ����� field.cpp � ������� makeRoad() ����� ������� ����� ������ �� �����������

void menu(int &level, bool &exitGame);
void mainGame(int &result, int level, int &waveLevel);
void result(int result, int waveLevel, bool &exitGame);

int main()
{
	// ���� ������� ��������� ���� 0 - ������ ����, 1 - ������ ����, 2 - ��������
	int res{ 0 };
	// ����� ������� ������?
	int level{ 1 };
	// �� ����� ����� ����������� ����?
	int waveLevel{ 0 };
	// ������� ����?
	bool exitGame{ 0 };

	while (1) {
		// ���������� ��� ���������
		res = 0; level = 1; waveLevel = 0;

		// ����� ������
		menu(level, exitGame);
		if (exitGame) {
			break;
		}

		// �������� ����
		mainGame(res, level, waveLevel);

		// ���������
		result(res, waveLevel, exitGame);
		if (exitGame) {
			break;
		}
	}

	return 0;
}