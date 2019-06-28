#include "stdafx.h"
//#include "MVector3.h"
#include "MMonster.h"
#include "include/structmember.h"


#include "../Monster/Monster.h"



PyTypeObject MMonsterType = {
	PyObject_HEAD_INIT(NULL,0)
};

static PyMemberDef MMonsterMembers[] =
{
	{(char*)"position",T_OBJECT_EX,offsetof(MMonster,position),0,(char*)""},
	{(char*)"ID",T_INT,offsetof(MMonster,ID),0,(char*)""},
	{(char*)"num",T_INT,offsetof(MMonster,num),0,(char*)""},
	{(char*)"team",T_INT,offsetof(MMonster,team),0,(char*)""},
	{(char*)"maxHP",T_FLOAT,offsetof(MMonster,maxHP),0,(char*)""},
	{(char*)"HP",T_FLOAT,offsetof(MMonster,HP),0,(char*)""},
	{(char*)"maxMP",T_FLOAT,offsetof(MMonster,maxMP),0,(char*)""},
	{(char*)"MP",T_FLOAT,offsetof(MMonster,MP),0,(char*)""},
	{(char*)"Attack",T_FLOAT,offsetof(MMonster,Attack),0,(char*)""},
	{(char*)"AttackEx",T_FLOAT,offsetof(MMonster,AttackEx),0,(char*)""},
	{(char*)"Defence",T_FLOAT,offsetof(MMonster,Defence),0,(char*)""},
	{(char*)"DefenceEx",T_FLOAT,offsetof(MMonster,DefenceEx),0,(char*)""},
	{(char*)"speed",T_FLOAT,offsetof(MMonster,speed),0,(char*)""},
	{(char*)"movespeed",T_OBJECT_EX,offsetof(MMonster,movespeed),0,(char*)""},
	{(char*)"state",T_OBJECT_EX,offsetof(MMonster,stateList),0,(char*)""},
	{NULL}
};

PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MMonster* self;
	self = (MMonster*)type->tp_alloc(type, 0);
	//self->position = (MVector3*)MVector3Type.tp_new(&MVector3Type, NULL, NULL);
	self->position = (MVector3*)MVector3Type.tp_new(&MVector3Type, NULL, NULL);
	self->ID = 999;
	self->num = 0;
	self->team = 0;
	self->maxHP = 0.f;
	self->HP = 0.f;
	self->maxMP = 0.f;
	self->MP = 0.f;
	self->Attack = 0.f;
	self->AttackEx = 0.f;
	self->Defence = 0.f;
	self->DefenceEx = 0.f;
	self->speed = 0.f;
	//self->movespeed = (MVector3*)MVector3Type.tp_new(&MVector3Type,NULL,NULL);
	//self->movespeed = PyObject_GC_New(MVector3, &MVector3Type);
	self->movespeed = (MVector3*)MVector3Type.tp_new(&MVector3Type, NULL, NULL);
	self->stateList = (PyListObject*)PyList_New(0);

	//PyObject_GC_Track(self);
	return PyObject_Init((PyObject*)self, self->ob_base.ob_type);;
}

int MMonsterInitialize(MMonster* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { 
		(char*)"position", 
		(char*)"ID", 
		(char*)"num",
		(char*)"team", 
		(char*)"maxHP", 
		(char*)"HP", 
		(char*)"maxMP", 
		(char*)"MP", 
		(char*)"Attack", 
		(char*)"AttackEx",
		(char*)"Defence",
		(char*)"DefenceEx",
		(char*)"speed",
		(char*)"movespeed",
		(char*)"state",
		NULL 
	};

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, 
		&self->position, 
		&self->ID, 
		&self->num,
		&self->team,
		&self->maxHP,
		&self->HP,
		&self->maxMP,
		&self->MP,
		&self->Attack,
		&self->AttackEx,
		&self->Defence,
		&self->DefenceEx,
		&self->speed,
		&self->movespeed,
		&self->stateList
	))
		return -1;
	return 0;
}

static int MMonsterTraverse(MMonster* self, visitproc visit, void* arg)
{
	Py_VISIT(self->position);
	Py_VISIT(self->movespeed);
	Py_VISIT(self->stateList);
	return 0;
}

static int MMonsterClear(MMonster* self)
{
	Py_CLEAR(self->position);
	Py_CLEAR(self->movespeed);
	Py_CLEAR(self->stateList);
	return 0;
}

static void MMonsterDestruct(MMonster* self)
{
	Py_XDECREF(self->position);
	Py_XDECREF(self->movespeed);
	Py_XDECREF(self->stateList);
	//PyObject_GC_UnTrack(self);
	//MMonsterClear(self);

	//PyObject_Del(self);
	//freeobj[freenum++] = (PyObject*)self;
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject* MMonsterGetPosition(MMonster* self, void* closure)
{
	Py_INCREF(self->position);
	return (PyObject*)self->position;
}
int MMonsterSetPosition(MMonster* self, PyObject* value, void* closure)
{
	if (value->ob_type != &MVector3Type)
		return -1;
	//Py_DECREF(self->position);
	Py_CLEAR(self->position);
	self->position = (MVector3*)value;
	Py_INCREF(self->position);
	return 0;
}

PyObject* MMonsterGetMoveSpeed(MMonster* self, void* closure)
{
	Py_INCREF(self->movespeed);
	return (PyObject*)self->movespeed;
}
int MMonsterSetMoveSpeed(MMonster* self, PyObject* value, void* closure)
{
	if (value->ob_type != &MVector3Type)
		return -1;
	//Py_DECREF(self->movespeed);
	Py_CLEAR(self->movespeed);
	self->movespeed = (MVector3*)value;
	Py_INCREF(self->movespeed);
	return 0;
}

PyObject* MMonsterGetState(MMonster* self, void* closure)
{
	Py_INCREF(self->stateList);
	return (PyObject*)self->stateList;
}
int MMonsterSetState(MMonster* self, PyObject* value, void* closure)
{
	if (value->ob_type != &PyListIter_Type)
		return -1;
	//Py_DECREF(self->stateList);
	Py_CLEAR(self->stateList);
	self->stateList = (PyListObject*)value;
	Py_INCREF(self->stateList);
	return 0;
}

static PyGetSetDef MMonsterGetSet[] =
{
	{(char*)"position",(getter)MMonsterGetPosition,(setter)MMonsterSetPosition,(char*)"",NULL},
	{(char*)"movespeed",(getter)MMonsterGetMoveSpeed,(setter)MMonsterSetMoveSpeed,(char*)"",NULL},
	{(char*)"state",(getter)MMonsterGetState,(setter)MMonsterSetState,(char*)"",NULL},
	{NULL}
};


void MMonsterInit()
{
	MMonsterType.tp_name = "SendGame.Monster";
	MMonsterType.tp_doc = "";
	MMonsterType.tp_basicsize = sizeof(MMonster);
	MMonsterType.tp_itemsize = 0;
	MMonsterType.tp_flags = Py_TPFLAGS_DEFAULT;
	

	MMonsterType.tp_members = MMonsterMembers;
	//MMonsterType.tp_methods = MMonsterMethods;
	MMonsterType.tp_new = MMonsterNew;
	MMonsterType.tp_init = (initproc)MMonsterInitialize;
	MMonsterType.tp_dealloc = (destructor)MMonsterDestruct;
	MMonsterType.tp_getset = MMonsterGetSet;

	//MMonsterType.tp_traverse = (traverseproc)MMonsterTraverse;
	//MMonsterType.tp_clear = (inquiry)MMonsterClear;
	//MMonsterType.tp_free = PyObject_GC_Del;
}

MMonster* CcreateMMonster(Monster* mon)
{
	//MMonster* m = (MMonster*)MMonsterType.tp_new(&MMonsterType, NULL, NULL);
	MMonster* m = (MMonster*)MMonsterNew(&MMonsterType,NULL,NULL);

	m->ID = mon->GetID();
	m->num = mon->Getnum();
	m->team = mon->Getteam();
	m->HP = mon->GetHP();
	m->maxHP = mon->GetMaxHP();
	m->MP = mon->GetMP();
	m->maxMP = mon->GetMaxMP();
	m->Attack = mon->GetAttack();
	m->AttackEx = mon->GetExAttack();
	m->Defence = mon->GetDefense();
	m->DefenceEx = mon->GetExDefense();
	m->speed = mon->GetSpeed();

	CVector3 cv = mon->Getpos();
	
	//MVector3* v = (MVector3*)MVector3Type.tp_new(&MVector3Type, NULL, NULL);
	/*MVector3* v = PyObject_New(MVector3, &MVector3Type);
	PyObject_Init((PyObject*)v,&MVector3Type);
	v->x = cv.x;
	v->y = cv.y;
	v->z = cv.z;*/
	m->position->x = cv.x;
	m->position->y = cv.y;
	m->position->z = cv.z;
	//PyObject_GC_Track(v);

	cv = mon->Getspeed();
	
	//v = (MVector3*)MVector3Type.tp_new(&MVector3Type, NULL, NULL);
	/*v = PyObject_New(MVector3, &MVector3Type);
	PyObject_Init((PyObject*)v, &MVector3Type);
	v->x = cv.x;
	v->y = cv.y;
	v->z = cv.z;*/
	m->movespeed->x = cv.x;
	m->movespeed->y = cv.y;
	m->movespeed->z = cv.z;
	//PyObject_GC_Track(v);
	
	//PyListObject* sl = (PyListObject*)PyList_New(0);
	int size = mon->GetAbnormalState().size();
	for (int i = 0; i < size; i++)
	{
		int abn = mon->GetAbnormalStateID(i);
		if (abn == 0)
			continue;
		PyList_Append((PyObject*)m->stateList, PyLong_FromLong(abn));
	}
	//m->stateList = sl;

	//PyObject_GC_Track(m);
	return m;
}
