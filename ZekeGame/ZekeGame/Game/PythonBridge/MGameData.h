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

PyObject* MGameDataNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int MGameDataInitialize(MGameData* self, PyObject* args, PyObject* kwds);
void MGameDataInit();
