#include "stdafx.h"
#include "MGameData.h"
#include "MMonster.h"
#include "MVector3.h"

#include "../GameData.h"
#include "../Monster/Monster.h"


PyTypeObject MGameDataType =
{
	PyVarObject_HEAD_INIT(NULL,0)
};

PyObject* MGameDataInit(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MGameData* self;
	self = (MGameData*)type->tp_alloc(type, 0);
	self->buddyCount = 0;
	self->enemyCount = 0;
	self->Buddys = (PyListObject*)PyList_New(0);
	self->Enemys = (PyListObject*)PyList_New(0);
	self->me = (MMonster*)MMonsterType.tp_alloc(&MMonsterType, 0);
}

void MGameDataInit()
{
}
