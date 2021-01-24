#pragma once

// эти параметры не изменять

// ширина клетки поля в пикселях
const int W{ 80 };
// кол-во типов противников плюс 1
const int ENEMIES_COUNT{ 6 };
// кол-во типов башен плюс 1
const int TOWERS_COUNT{ 7 };
// кол-во типов блоков, которые можно поставить на дорогу плюс 1
const int FIELD_BLOCKS_COUNT{ 3 };

// остальные параметры можно изменять для настройки размера поля и баланса

// кол-во строк, максимум 10 для 1920x1080 при W = 80
const int ROWS{ 10 };
// кол-во столбцов, минимум 11 для корректного интерфейса
const int COLS{ 11 };

// стартовые деньги для каждого уровня
const int START_MONEY[7]{ 0, 30, 30, 30, 30, 50, 30 };

// далее индекс массива равен типу врага/башни/блока

// кол-во hp у врагов
const int ENEMIES_HP[ENEMIES_COUNT]{ 0,180,360,720,900,1800 };
// кол-во монет, падающих с врагов
const int ENEMIES_COINS[ENEMIES_COUNT]{ 0,2,4,5,6,8 };
// скорость врагов
const double ENEMIES_SPEED[ENEMIES_COUNT]{ 0,2,1.8,1.8,2.2,2.2 };
// урон врагов
const int ENEMIES_DAMAGE[ENEMIES_COUNT]{ 0,1,1,2,2,3 };

// стоимости башен
const int TOWERS_PRICE[TOWERS_COUNT]{ 0,10,30,50,80,120,150 };
// урон башен
const int TOWERS_DAMAGE[TOWERS_COUNT]{ 0,1,3,5,8,12,15 };

// стоимост блоков на поле
const int BLOCKS_PRICE[FIELD_BLOCKS_COUNT]{ 0,10,20 };
// здоворье останавливающего блока
const int STOP_BLOCK_HP{ 1000 };