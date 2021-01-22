#pragma once

// ������ ������ ���� � ��������, �� ��������
const int W{ 80 };

// ��������� ��������� ����� �������� ��� ��������� ������� ���� � �������

// ���-�� �����
const int ROWS{ 9 };
// ���-�� ��������
const int COLS{ 9 };

// ��������� ������
const int START_MONEY{ 30 };

// ����� ������ ������� ����� ���� ����������/�����

// ���-�� ����� ����������� ����� 1
const int ENEMIES_COUNT{ 5 };
// ���-�� hp � �����������
const int ENEMIES_HP[ENEMIES_COUNT]{ 0,120,360,600,1200 };
// ���-�� �����, �������� � �����������
const int ENEMIES_COINS[ENEMIES_COUNT]{ 0,1,3,5,10 };
// �������� �����������
const double ENEMIES_SPEED[ENEMIES_COUNT]{ 0,2,2.4,1.8,1.8 };

// ���-�� ����� ����� ����� 1
const int TOWERS_COUNT{ 7 };
// ��������� �����
const int TOWERS_PRICE[TOWERS_COUNT]{ 0,10,30,50,80,120,150 };
// ���� ����� ������ ����
const int TOWERS_DAMAGE[TOWERS_COUNT]{ 0,1,3,5,8,12,15 };