#pragma once

#include "MMonster.h"

typedef struct
{
	PyObject_HEAD
	int buddyCount = 0;
	int enemyCount = 0;
	PyListObject* Buddys = nullptr;
	PyListObject* Enemys = nullptr;
	MMonster* me = nullptr;
} MGameData;

extern PyTypeObject MGameDataType;

PyObject* MGameDataNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
int MGameDataInitialize(MGameData* self, PyObject* args, PyObject* kwds);
void MGameDataInit();
