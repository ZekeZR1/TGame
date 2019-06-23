#include "stdafx.h"
//#include "MVector3.h"
#include "MMonster.h"
#include "include/structmember.h"


#include "../Monster/Monster.h"

PyTypeObject MMonsterType = {
	PyVarObject_HEAD_INIT(NULL,0)
};

static PyMemberDef MMonsterMembers[] =
{
	{(char*)"position",T_OBJECT,offsetof(MMonster,position),0,(char*)""},
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
	{(char*)"movespeed",T_OBJECT,offsetof(MMonster,movespeed),0,(char*)""},
	{(char*)"state",T_OBJECT,offsetof(MMonster,stateList),0,(char*)""},
	{NULL}
};

static PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MMonster* self;
	self = (MMonster*)type->tp_alloc(type, 0);
	self->position = PyObject_New(MVector3, &MVector3Type);
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
	self->movespeed = PyObject_New(MVector3, &MVector3Type);
	self->stateList = (PyListObject*)PyList_New(0);

	return (PyObject*)self;
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

void MMonsterDestruct(MMonster* self)
{
	Py_DECREF(self->position);
	Py_DECREF(self->movespeed);
	Py_DECREF(self->stateList);

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
	Py_DECREF(self->position);
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
	Py_DECREF(self->movespeed);
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
	Py_DECREF(self->stateList);
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
	MMonsterType.tp_name = "SendGame.Vector3";
	MMonsterType.tp_doc = "";
	MMonsterType.tp_basicsize = sizeof(MVector3);
	MMonsterType.tp_itemsize = 0;
	MMonsterType.tp_flags = Py_TPFLAGS_DEFAULT;
	MMonsterType.tp_new = PyType_GenericNew;

	MMonsterType.tp_members = MMonsterMembers;
	//MMonsterType.tp_methods = MMonsterMethods;
	MMonsterType.tp_new = MMonsterNew;
	MMonsterType.tp_init = (initproc)MMonsterInitialize;
	MMonsterType.tp_dealloc = (destructor)MMonsterDestruct;
	MMonsterType.tp_getset = MMonsterGetSet;
}

MMonster* CcreateMMonster(Monster* mon)
{
	MMonster* m = PyObject_New(MMonster, &MMonsterType);
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
	MVector3* v = PyObject_New(MVector3, &MVector3Type);
	v->x = cv.x;
	v->y = cv.y;
	v->z = cv.z;
	m->position = v;
	cv = mon->Getspeed();
	v = PyObject_New(MVector3, &MVector3Type);
	v->x = cv.x;
	v->y = cv.y;
	v->z = cv.z;
	m->movespeed = v;
	PyListObject* sl = (PyListObject*)PyList_New(0);

	return nullptr;
}
