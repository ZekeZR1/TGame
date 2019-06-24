#pragma once

#include "MMonster.h"

typedef struct
{
	PyObject_HEAD
	int buddyCount;
	int enemyCount;
	PyListObject* Buddys;
	PyListObject* Enemys;
	MMonster* me;
} MGameData;

extern PyTypeObject MGameDataType;
void MGameDataInit();
