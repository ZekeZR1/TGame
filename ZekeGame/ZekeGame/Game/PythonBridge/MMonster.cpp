#include "stdafx.h"
#include "MMonster.h"
#include "include/structmember.h"
#include "MVector3.h"

typedef struct {
	PyObject_HEAD
	MVector3* position;
	int ID;
	int team;
	float HP;
	float MP;
	float Attack;
	float AttackEx;
	float Defence;
	float DefenceEx;
	float speed;
	MVector3* movespeed;
	int state[10];

}MMonster;

PyTypeObject MMonsterType = {
	PyVarObject_HEAD_INIT(NULL,0)
};

static PyMemberDef MMonsterMember[] =
{
	{(char*)"position",T_OBJECT,offsetof(MMonster,position),0,(char*)""},
	{(char*)"ID",T_INT,offsetof(MMonster,ID),0,(char*)""},
	{(char*)"team",T_INT,offsetof(MMonster,team),0,(char*)""},
	{(char*)"HP",T_FLOAT,offsetof(MMonster,HP),0,(char*)""},
	{(char*)"MP",T_FLOAT,offsetof(MMonster,MP),0,(char*)""},
	{(char*)"Attack",T_FLOAT,offsetof(MMonster,Attack),0,(char*)""},
	{(char*)"AttackEx",T_FLOAT,offsetof(MMonster,AttackEx),0,(char*)""},
	{(char*)"Defence",T_FLOAT,offsetof(MMonster,Defence),0,(char*)""},
	{(char*)"DefenceEx",T_FLOAT,offsetof(MMonster,DefenceEx),0,(char*)""},
	{(char*)"speed",T_FLOAT,offsetof(MMonster,speed),0,(char*)""},
	{(char*)"movespeed",T_OBJECT,offsetof(MMonster,movespeed),0,(char*)""},
	{(char*)"state",T_FLOAT,offsetof(MMonster,state),0,(char*)""},
	{NULL}
};

static PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MMonster* self;
	self = (MMonster*)type->tp_alloc(type, 0);

}

void MMonsterInit()
{
}
