#include "stdafx.h"
#include "MMonster.h"
#include "include/structmember.h"
#include "MVector3.h"

typedef struct {
	PyObject_HEAD
	MVector3* position;
	int ID;
	int team;
	float maxHP;
	float HP;
	float maxMP;
	float MP;
	float Attack;
	float AttackEx;
	float Defence;
	float DefenceEx;
	float speed;
	MVector3* movespeed;
	PyListObject* stateList;

}MMonster;

PyTypeObject MMonsterType = {
	PyVarObject_HEAD_INIT(NULL,0)
};

static PyMemberDef MMonsterMembers[] =
{
	{(char*)"position",T_OBJECT,offsetof(MMonster,position),0,(char*)""},
	{(char*)"ID",T_INT,offsetof(MMonster,ID),0,(char*)""},
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
	{(char*)"state",T_FLOAT,offsetof(MMonster,stateList),0,(char*)""},
	{NULL}
};

static PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MMonster* self;
	self = (MMonster*)type->tp_alloc(type, 0);
	self->position = PyObject_New(MVector3, &MVector3Type);
	self->ID = 999;
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
	int size = PyList_Size((PyObject*)self->stateList);
	for (int i = 0; i < size; i++)
		Py_DECREF(self->stateList->ob_item[i]);
	Py_DECREF(self->stateList);

	Py_TYPE(self)->tp_free((PyObject*)self);
}




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
}