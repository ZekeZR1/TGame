#include "stdafx.h"
#include "include/structmember.h"

#include "MGameData.h"
//#include "MMonster.h"
#include "MVector3.h"

#include "../GameData.h"
#include "../Monster/Monster.h"


PyTypeObject MGameDataType =
{
	PyVarObject_HEAD_INIT(NULL,0)
};



PyObject* MGameDataNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MGameData* self;
	self = (MGameData*)type->tp_alloc(type, 0);
	self->buddyCount = 0;
	self->enemyCount = 0;
	self->Buddys = (PyListObject*)PyList_New(0);
	self->Enemys = (PyListObject*)PyList_New(0);
	self->me = PyObject_New(MMonster,&MMonsterType);
	return (PyObject*)self;
}

int MGameDataInitialize(MGameData* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"buddyCount",(char*)"enemyCount",(char*)"Buddys",(char*) "Enemys",(char*) "me" ,NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, &self->buddyCount, &self->enemyCount, &self->Buddys, &self->Enemys, &self->me))
		return -1;

	int num = PyLong_AsLong(PyList_GetItem(args, 0));
	int team = PyLong_AsLong(PyList_GetItem(args, 1));

	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == team)//buddy
		{
			
		}
		else//enemy
		{

		}
	}
	return 0;
}

void MGameDataDestruct(MGameData* self)
{
	Py_DECREF(self->Buddys);
	Py_DECREF(self->Enemys);
	Py_DECREF(self->me);

	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMemberDef MGameDataMembers[] =
{
	{(char*)"buddyCount",T_INT,offsetof(MGameData,buddyCount),0,(char*)""},
	{(char*)"enemyCount",T_INT,offsetof(MGameData,enemyCount),0,(char*)""},
	{(char*)"Buddys",T_OBJECT,offsetof(MGameData,Buddys),0,(char*)""},
	{(char*)"Enemys",T_OBJECT,offsetof(MGameData,Enemys),0,(char*)""},
	{(char*)"me",T_OBJECT,offsetof(MGameData,me),0,(char*)""},
	{NULL}
};

/*
	getset
*/
PyObject* MGameDataGetBuddys(MGameData* self, void* closure)
{
	Py_INCREF(self->Buddys);
	return (PyObject*)self->Buddys;
}
int MGameDataSetBuddys(MGameData* self, PyObject* value, void* closure)
{
	if (value->ob_type != &PyListIter_Type)
		return -1;
	Py_DECREF(self->Buddys);
	self->Buddys = (PyListObject*)value;
	Py_INCREF(self->Buddys);
	return 0;
}

PyObject* MGameDataGetEnemys(MGameData* self, void* closure)
{
	Py_INCREF(self->Enemys);
	return (PyObject*)self->Enemys;
}
int MGameDataSetEnemys(MGameData* self, PyObject* value, void* closure)
{
	if (value->ob_type != &PyListIter_Type)
		return -1;
	Py_DECREF(self->Enemys);
	self->Enemys = (PyListObject*)value;
	Py_INCREF(self->Enemys);
	return 0;
}

PyObject* MGameDataGetme(MGameData* self, void* closure)
{
	Py_INCREF(self->me);
	return (PyObject*)self->me;
}
int MGameDataSetme(MGameData* self, PyObject* value, void* closure)
{
	if (value->ob_type != &MMonsterType)
		return -1;
	Py_DECREF(self->me);
	self->me = (MMonster*)value;
	Py_INCREF(self->me);
	return 0;
}
static PyGetSetDef MGameDataGetSet[] =
{
	{(char*)"Buddys",(getter)MGameDataGetBuddys,(setter)MGameDataSetBuddys,(char*)"",NULL},
	{(char*)"Enemys",(getter)MGameDataGetEnemys,(setter)MGameDataSetEnemys,(char*)"",NULL},
	{(char*)"me",(getter)MGameDataGetme,(setter)MGameDataSetme,(char*)"",NULL},
	{NULL}
};

void MGameDataInit()
{
	MGameDataType.tp_name = "SendGame.GameData";
	MGameDataType.tp_doc = "";
	MGameDataType.tp_basicsize = sizeof(MVector3);
	MGameDataType.tp_itemsize = 0;
	MGameDataType.tp_flags = Py_TPFLAGS_DEFAULT;
	MGameDataType.tp_new = PyType_GenericNew;

	MGameDataType.tp_members = MGameDataMembers;
	//MMonsterType.tp_methods = MMonsterMethods;
	MGameDataType.tp_new = MGameDataNew;
	MGameDataType.tp_init = (initproc)MGameDataInitialize;
	MGameDataType.tp_dealloc = (destructor)MGameDataDestruct;
	MGameDataType.tp_getset = MGameDataGetSet;
}
