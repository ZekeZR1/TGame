#pragma once

#include "MVector3.h"

typedef struct {
	PyObject_HEAD
	MVector3* position = nullptr;
	int ID = 0;
	int num = 0;
	int team = 0;
	float maxHP = 0.f;
	float HP = 0.f;
	float maxMP = 0.f;
	float MP = 0.f;
	float Attack = 0.f;
	float AttackEx = 0.f;
	float Defence = 0.f;
	float DefenceEx = 0.f;
	float speed = 0.f;
	MVector3* movespeed = nullptr;
	PyListObject* stateList = nullptr;

}MMonster;

extern PyTypeObject MMonsterType;
PyObject* MMonsterNew(PyTypeObject* type, PyObject* args, PyObject* kwds);
void MMonsterInit();

class Monster;
MMonster* CcreateMMonster(Monster* mon);