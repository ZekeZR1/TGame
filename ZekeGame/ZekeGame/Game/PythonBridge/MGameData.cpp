#include "stdafx.h"
#include "include/structmember.h"

#include "MGameData.h"
//#include "MMonster.h"
#include "MVector3.h"

#include "../GameData.h"
//#include "../Monster/Monster.h"


PyTypeObject MGameDataType =
{
	PyObject_HEAD_INIT(NULL,0)
};



PyObject* MGameDataNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MGameData* self;
	self = (MGameData*)type->tp_alloc(type, 0);
	self->buddyCount = 0;
	self->enemyCount = 0;
	self->Buddys = (PyListObject*)PyList_New(0);
	self->Enemys = (PyListObject*)PyList_New(0);
	//self->me = (MMonster*)MMonsterType.tp_new(&MMonsterType, NULL, NULL);
	//self->me = PyObject_GC_New(MMonster,&MMonsterType);
	//self->me = (MMonster*)MMonsterType.tp_new(&MMonsterType,NULL,NULL);

	//PyObject_GC_Track(self);
	return PyObject_Init((PyObject*)self,self->ob_base.ob_type);
}

int MGameDataInitialize(MGameData* self, PyObject* args, PyObject* kwds)
{
	/*static char* kwlist[] = { (char*)"buddyCount",(char*)"enemyCount",(char*)"Buddys",(char*) "Enemys",(char*) "me" ,NULL};
	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, &self->buddyCount, &self->enemyCount, &self->Buddys, &self->Enemys, &self->me))
		return -1;*/

	int num = PyLong_AsLong(PyTuple_GetItem(args, 0));
	int team = PyLong_AsLong(PyTuple_GetItem(args, 1));

	self->buddyCount = 0;
	self->enemyCount = 0;
	//self->Buddys = (PyListObject*)PyList_New(0);
	//self->Enemys = (PyListObject*)PyList_New(0);

	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		MMonster* mmon = CcreateMMonster(mon);
		if (mmon->team == team)//buddy
		{
			if (mmon->num == num)//IT'S ME!!!
			{
				Py_INCREF(mmon);
				//Py_DECREF(self->me);
				//Py_CLEAR(self->me);
				self->me = mmon;
			}
			PyList_Append((PyObject*)self->Buddys, (PyObject*)mmon);
			//Py_DECREF(mmon);
			self->buddyCount++;
		}
		else//enemy
		{
			PyList_Append((PyObject*)self->Enemys, (PyObject*)mmon);
			//Py_DECREF(mmon);
			self->enemyCount++;
		}
	}
	return 0;
}

static int MGameDataTraverse(MGameData* self, visitproc visit, void* arg)
{
	Py_VISIT(self->Buddys);
	Py_VISIT(self->Enemys);
	Py_VISIT(self->me);
	return 0;
}

static int MGameDataClear(MGameData* self)
{
	Py_CLEAR(self->me);
	Py_CLEAR(self->Buddys);
	Py_CLEAR(self->Enemys);
	return 0;
}

void MGameDataDestruct(MGameData* self)
{
	Py_XDECREF(self->me);
	Py_XDECREF(self->Buddys);
	Py_XDECREF(self->Enemys);
	

	//PyObject_GC_UnTrack(self);
	//MGameDataClear(self);

	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMemberDef MGameDataMembers[] =
{
	{(char*)"buddyCount",T_INT,offsetof(MGameData,buddyCount),0,(char*)""},
	{(char*)"enemyCount",T_INT,offsetof(MGameData,enemyCount),0,(char*)""},
	{(char*)"Buddys",T_OBJECT_EX,offsetof(MGameData,Buddys),0,(char*)""},
	{(char*)"Enemys",T_OBJECT_EX,offsetof(MGameData,Enemys),0,(char*)""},
	{(char*)"me",T_OBJECT_EX,offsetof(MGameData,me),0,(char*)""},
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
	//Py_DECREF(self->Buddys);
	Py_CLEAR(self->Buddys);
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
	//Py_CLEAR(self->Enemys);
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
	//Py_DECREF(self->me);
	Py_CLEAR(self->me);
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
	MGameDataType.tp_basicsize = sizeof(MGameData);
	MGameDataType.tp_itemsize = 0;
	MGameDataType.tp_flags = Py_TPFLAGS_DEFAULT ;
	//MGameDataType.tp_new = PyType_GenericNew;

	MGameDataType.tp_members = MGameDataMembers;
	//MMonsterType.tp_methods = MMonsterMethods;
	MGameDataType.tp_new = MGameDataNew;
	MGameDataType.tp_init = (initproc)MGameDataInitialize;
	MGameDataType.tp_dealloc = (destructor)MGameDataDestruct;
	MGameDataType.tp_getset = MGameDataGetSet;

	//MGameDataType.tp_traverse = (traverseproc)MGameDataTraverse;
	//MGameDataType.tp_clear = (inquiry)MGameDataClear;
}
