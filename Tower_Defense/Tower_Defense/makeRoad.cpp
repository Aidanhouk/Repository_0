#include "field.h"

#include "consts.h"
#include "roadCell.h"

void Field::makeRoad()
{
	// сначала ставитс€ стартово€ €чейка (она находитс€ вне пол€), остальные добавл€ютс€ через функцию addCell
	// можно построить любую дорогу, зна€ координаты
	RoadCell *startCell;
	switch (m_level)
	{
	case 1:
	{
		startCell = new RoadCell(ROWS, 5);
		m_startCell = startCell;
		m_finishCell = startCell;

		for (int i = ROWS - 1; i > 0; --i) {
			addRoadCell(i, 5);
		}
		for (int i = 6; i < COLS - 1; ++i) {
			addRoadCell(1, i);
		}
		for (int i = 2; i < ROWS - 1; ++i) {
			addRoadCell(i, COLS - 2);
		}
		for (int i = COLS - 3; i > 0; --i) {
			addRoadCell(ROWS - 2, i);
		}

		for (int i = ROWS - 3; i > 0; --i) {
			addRoadCell(i, 1);
		}
		for (int i = 2; i < 4; ++i) {
			addRoadCell(1, i);
		}
		for (int i = 2; i < ROWS - 3; ++i) {
			addRoadCell(i, 3);
		}
		for (int i = 4; i < COLS - 3; ++i) {
			addRoadCell(ROWS - 4, i);
		}
		for (int i = ROWS - 5; i > 2; --i) {
			addRoadCell(i, COLS - 4);
		}
	}
	break;
	case 2:
	{
		startCell = new RoadCell(ROWS, 4);
		m_startCell = startCell;
		m_finishCell = startCell;

		for (int i = ROWS - 1; i > -1; --i) {
			addRoadCell(i, COLS - 7);
		}
		for (int i = COLS - 8; i > COLS - 10; --i) {
			addRoadCell(0, i);
		}

		for (int i = 1; i < ROWS; ++i) {
			addRoadCell(i, COLS - 9);
		}
		for (int i = COLS - 10; i > -1; --i) {
			addRoadCell(ROWS - 1, i);
		}

		for (int i = ROWS - 2; i > ROWS - 4; --i) {
			addRoadCell(i, 0);
		}
		for (int i = 1; i < COLS; ++i) {
			addRoadCell(ROWS - 3, i);
		}
		for (int i = ROWS - 2; i < ROWS; ++i) {
			addRoadCell(i, COLS - 1);
		}

		for (int i = COLS - 2; i > COLS - 4; --i) {
			addRoadCell(ROWS - 1, i);
		}
		for (int i = ROWS - 2; i > -1; --i) {
			addRoadCell(i, COLS - 3);
		}

		for (int i = COLS - 4; i > COLS - 6; --i) {
			addRoadCell(0, i);
		}
		for (int i = 1; i < ROWS; ++i) {
			addRoadCell(i, COLS - 5);
		}

		addRoadCell(ROWS - 1, COLS - 6);
	}
	break;
	case 3:
	{
		startCell = new RoadCell(ROWS - 4, -1);
		m_startCell = startCell;
		m_finishCell = startCell;

		addRoadCell(ROWS - 4, 0);
		addRoadCell(ROWS - 3, 0);
		addRoadCell(ROWS - 3, 1);
		addRoadCell(ROWS - 2, 1);
		addRoadCell(ROWS - 2, 2);
		addRoadCell(ROWS - 1, 2);
		for (int i = 3; i < COLS - 2; ++i) {
			addRoadCell(ROWS - 1, i);
		}
		addRoadCell(ROWS - 2, COLS - 3);
		addRoadCell(ROWS - 2, COLS - 2);
		addRoadCell(ROWS - 3, COLS - 2);
		addRoadCell(ROWS - 3, COLS - 1);
		for (int i = ROWS - 4; i > 1; --i) {
			addRoadCell(i, COLS - 1);
		}
		addRoadCell(2, COLS - 2);
		addRoadCell(1, COLS - 2);
		addRoadCell(1, COLS - 3);
		addRoadCell(0, COLS - 3);
		for (int i = COLS - 4; i > 1; --i) {
			addRoadCell(0, i);
		}
		addRoadCell(1, 2);
		addRoadCell(1, 1);
		addRoadCell(2, 1);
		addRoadCell(2, 0);
		for (int i = 3; i < 6; ++i) {
			addRoadCell(i, 0);
		}

		for (int i = 1; i < 3; ++i) {
			addRoadCell(5, i);
		}
		addRoadCell(6, 2);
		addRoadCell(6, 3);
		addRoadCell(7, 3);
		for (int i = 4; i < COLS - 3; ++i) {
			addRoadCell(7, i);
		}
		addRoadCell(6, COLS - 4);
		for (int i = ROWS - 4; i > 2; --i) {
			addRoadCell(i, COLS - 3);
		}
		addRoadCell(3, COLS - 4);
		for (int i = COLS - 4; i > 2; --i) {
			addRoadCell(2, i);
		}
		addRoadCell(3, 3);
		addRoadCell(3, 2);
		addRoadCell(4, 2);
		addRoadCell(4, 1);
	}
	break;
	case 4:
	{
		startCell = new RoadCell(8, -1);
		m_startCell = startCell;
		m_finishCell = startCell;

		for (int i = 0; i < 5; ++i) {
			addRoadCell(ROWS - 2, i);
		}
		for (int i = ROWS - 3; i > 2; --i) {
			addRoadCell(i, 4);
		}
		for (int i = 5; i < COLS - 3; ++i) {
			addRoadCell(3, i);
		}
		for (int i = 4; i < ROWS - 3; ++i) {
			addRoadCell(i, COLS - 4);
		}
		for (int i = COLS - 5; i > 0; --i) {
			addRoadCell(ROWS - 4, i);
		}

		for (int i = ROWS - 5; i > 0; --i) {
			addRoadCell(i, 1);
		}
		for (int i = 2; i < COLS - 1; ++i) {
			addRoadCell(1, i);
		}
		for (int i = 2; i < ROWS; ++i) {
			addRoadCell(i, COLS - 2);
		}
	}
	break;
	case 5:
	{
		startCell = new RoadCell(ROWS, 0);
		m_startCell = startCell;
		m_finishCell = startCell;

		for (int i = ROWS - 1; i > -1; --i) {
			addRoadCell(i, 0);
		}
		for (int i = 1; i < COLS; ++i) {
			addRoadCell(0, i);
		}
		for (int i = 1; i < 3; ++i) {
			addRoadCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 1; --i) {
			addRoadCell(2, i);
		}
		for (int i = 3; i < ROWS; ++i) {
			addRoadCell(i, 2);
		}

		for (int i = 3; i < 5; ++i) {
			addRoadCell(ROWS - 1, i);
		}
		for (int i = ROWS - 2; i > 3; --i) {
			addRoadCell(i, 4);
		}
		for (int i = 5; i < COLS; ++i) {
			addRoadCell(4, i);
		}
		for (int i = 5; i < 7; ++i) {
			addRoadCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 5; --i) {
			addRoadCell(6, i);
		}
		for (int i = 7; i < ROWS; ++i) {
			addRoadCell(i, 6);
		}

		for (int i = 7; i < COLS; ++i) {
			addRoadCell(ROWS - 1, i);
		}
	}
	break;
	case 6:
	{
		startCell = new RoadCell(ROWS, 1);
		m_startCell = startCell;
		m_finishCell = startCell;

		for (int i = ROWS - 1; i > 0; --i) {
			addRoadCell(i, 1);
		}
		for (int i = 2; i < COLS - 1; ++i) {
			addRoadCell(1, i);
		}
		for (int i = 2; i < ROWS - 1; ++i) {
			addRoadCell(i, COLS - 2);
		}
		for (int i = COLS - 3; i > 2; --i) {
			addRoadCell(ROWS - 2, i);
		}

		for (int i = ROWS - 3; i > 2; --i) {
			addRoadCell(i, 3);
		}
		for (int i = 4; i < COLS - 3; ++i) {
			addRoadCell(3, i);
		}
		for (int i = 4; i < ROWS - 3; ++i) {
			addRoadCell(i, COLS - 4);
		}
		for (int i = COLS - 5; i > 4; --i) {
			addRoadCell(ROWS - 4, i);
		}

		addRoadCell(ROWS - 5, 5);
	}
	break;
	}
}