#include "_AI.h"

#include "globals.h"
#include "field.h"

void AI::_AI_makes_move(int & row, int & col)
{
	// ������� ������ �����
	std::vector<int> moves{ field->getMovesVector() };

	// ������ AI
	bool markAI{ !static_cast<bool>(moves.size() % 2) };
	// ����� ��������� ����� / �� ���� ��������� ���������
	int q{ -1 };

	// ���� 1-�� ���, �� ��������� ������ � ����� ������� ����
	if (!moves.size()) {
		moves.push_back(0);
		row = 0;
		col = 0;
	}
	else {
		// ���� ������ ���� �� 3, �� ������� ���������� checkLines
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			field->setMovesVector(moves);
			return;
		}
		// ���� ������ �� ����������, �� ���� ������
		if (n != 3) {
			int i;
			while (1) {
				i = rand() % (n * n);
				bool f = 0;
				for (auto & var : moves) {
					if (var == i) {
						f = 1;
						break;
					}
				}
				if (!f) {
					break;
				}
			}
			moves.push_back(i);
			row = i / n;
			col = i % n;
		}
		else {
			// ���� AI ������ ������� �������
			if (markAI == 1) {
				_AIMovesCrosses(moves, row, col);
			}
			// ���� �����
			else {
				_AIMovesNoughts(moves, row, col);
			}
		}
	}
	field->setMovesVector(moves);
}