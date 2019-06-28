#pragma once

#include "MVector3.h"

typedef struct {
	PyObject_HEAD
	MVector3* position;
	int ID;
	int num;
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

extern PyTypeObject MMonsterType;
PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
void MMonsterInit();

class Monster;
MMonster* CcreateMMonster(Monster* mon);