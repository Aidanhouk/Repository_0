#pragma once

// ��� ��������� �� ��������

// ������ ������ ���� � ��������
const int W{ 80 };
// ���-�� ����� ����������� ���� 1
const int ENEMIES_COUNT{ 5 };
// ���-�� ����� ����� ���� 1
const int TOWERS_COUNT{ 7 };
// ���-�� ����� ������, ������� ����� ��������� �� ������ ���� 1
const int FIELD_BLOCKS_COUNT{ 3 };

// ��������� ��������� ����� �������� ��� ��������� ������� ���� � �������

// ���-�� �����, �������� 10 ��� 1920x1080
const int ROWS{ 10 };
// ���-�� ��������, ������� 11
const int COLS{ 11 };

// ��������� ������
const int START_MONEY{ 30 };

// ����� ������ ������� ����� ���� �����/�����

// ���-�� hp � ������
const int ENEMIES_HP[ENEMIES_COUNT]{ 0,120,360,600,1200 };
// ���-�� �����, �������� � ������
const int ENEMIES_COINS[ENEMIES_COUNT]{ 0,1,3,5,10 };
// �������� ������
const double ENEMIES_SPEED[ENEMIES_COUNT]{ 0,2,2.4,1.8,1.8 };
// ���� ������
const int ENEMIES_DAMAGE[ENEMIES_COUNT]{ 0,1,3,5,10 };

// ��������� �����
const int TOWERS_PRICE[TOWERS_COUNT]{ 0,10,30,50,80,120,150 };
// ���� �����
const int TOWERS_DAMAGE[TOWERS_COUNT]{ 0,1,3,5,8,12,15 };

// �������� ������ �� ����
const int BLOCKS_PRICE[FIELD_BLOCKS_COUNT]{ 0,10,20 };
// �������� ���������������� �����
const int STOP_BLOCK_HP{ 1000 };