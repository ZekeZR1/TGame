#include "stdafx.h"
#include "PythonBridge.h"
#include "../Monster/Monster.h"


static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	PyObject *x, *y, *z;
	x = PyLong_FromDouble(g_mons[0]->Getpos().x);
	y = PyLong_FromDouble(g_mons[0]->Getpos().y);
	z = PyLong_FromDouble(g_mons[0]->Getpos().z);

	PyObject* pos = PyTuple_New(0);
	PyTuple_SetItem(pos, 0, x);

	pos = PyTuple_New(1);
	PyTuple_SetItem(pos, 1, y);

	pos = PyTuple_New(2);
	PyTuple_SetItem(pos, 2, z);
	return pos;
}

static PyObject* GetMyHP(PyObject* self, PyObject* args)
{
	PyObject* pHP = PyLong_FromLong(g_mons[0]->GetHP());
	return pHP;
}

static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	PyObject *x1, *y1, *z1;
	x1 = PyLong_FromDouble(g_mons[0]->Getpos().x);
	y1 = PyLong_FromDouble(g_mons[0]->Getpos().y);
	z1 = PyLong_FromDouble(g_mons[0]->Getpos().z);

	PyObject* pos1 = PyTuple_New(0);
	PyTuple_SetItem(pos1, 0, x1);

	pos1 = PyTuple_New(1);
	PyTuple_SetItem(pos1, 1, y1);

	pos1 = PyTuple_New(2);
	PyTuple_SetItem(pos1, 2, z1);

	PyObject *x2, *y2, *z2;
	x2 = PyLong_FromDouble(g_mons[1]->Getpos().x);
	y2 = PyLong_FromDouble(g_mons[1]->Getpos().y);
	z2 = PyLong_FromDouble(g_mons[1]->Getpos().z);

	PyObject* pos2 = PyTuple_New(0);
	PyTuple_SetItem(pos2, 0, x2);

	pos2 = PyTuple_New(1);
	PyTuple_SetItem(pos2, 1, y2);

	pos2 = PyTuple_New(2);
	PyTuple_SetItem(pos2, 2, z2);

	PyObject *x3, *y3, *z3;
	x3 = PyLong_FromDouble(g_mons[2]->Getpos().x);
	y3 = PyLong_FromDouble(g_mons[2]->Getpos().y);
	z3 = PyLong_FromDouble(g_mons[2]->Getpos().z);

	PyObject* pos3 = PyTuple_New(0);
	PyTuple_SetItem(pos3, 0, x3);

	pos3 = PyTuple_New(1);
	PyTuple_SetItem(pos3, 1, y3);

	pos3 = PyTuple_New(2);
	PyTuple_SetItem(pos3, 2, z3);

	PyObject* poss = PyTuple_New(0);
	PyTuple_SetItem(poss, 0, pos1);
	poss = PyTuple_New(1);
	PyTuple_SetItem(poss, 1, pos2);
	poss = PyTuple_New(2);
	PyTuple_SetItem(poss, 2, pos3);

	return poss;
}

static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject *x1, *y1, *z1;
	x1 = PyLong_FromDouble(g_mons[3]->Getpos().x);
	y1 = PyLong_FromDouble(g_mons[3]->Getpos().y);
	z1 = PyLong_FromDouble(g_mons[3]->Getpos().z);

	PyObject* pos1 = PyTuple_New(0);
	PyTuple_SetItem(pos1, 0, x1);

	pos1 = PyTuple_New(1);
	PyTuple_SetItem(pos1, 1, y1);

	pos1 = PyTuple_New(2);
	PyTuple_SetItem(pos1, 2, z1);

	PyObject *x2, *y2, *z2;
	x2 = PyLong_FromDouble(g_mons[4]->Getpos().x);
	y2 = PyLong_FromDouble(g_mons[4]->Getpos().y);
	z2 = PyLong_FromDouble(g_mons[4]->Getpos().z);

	PyObject* pos2 = PyTuple_New(0);
	PyTuple_SetItem(pos2, 0, x2);

	pos2 = PyTuple_New(1);
	PyTuple_SetItem(pos2, 1, y2);

	pos2 = PyTuple_New(2);
	PyTuple_SetItem(pos2, 2, z2);

	PyObject *x3, *y3, *z3;
	x3 = PyLong_FromDouble(g_mons[5]->Getpos().x);
	y3 = PyLong_FromDouble(g_mons[5]->Getpos().y);
	z3 = PyLong_FromDouble(g_mons[5]->Getpos().z);

	PyObject* pos3 = PyTuple_New(0);
	PyTuple_SetItem(pos3, 0, x3);

	pos3 = PyTuple_New(1);
	PyTuple_SetItem(pos3, 1, y3);

	pos3 = PyTuple_New(2);
	PyTuple_SetItem(pos3, 2, z3);

	PyObject* poss = PyTuple_New(0);
	PyTuple_SetItem(poss, 0, pos1);
	poss = PyTuple_New(1);
	PyTuple_SetItem(poss, 1, pos2);
	poss = PyTuple_New(2);
	PyTuple_SetItem(poss, 2, pos3);

	return poss;
}

static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},
	{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},
	{NULL,NULL,0,NULL}
};

static PyModuleDef pModule =
{
	PyModuleDef_HEAD_INIT,
	"SendGame",
	NULL,
	-1,
	methods,
	NULL,
	NULL,
	NULL,
	NULL
};

void PythonBridge::py_exe(Monster* meMons)
{
	g_mons[0] = meMons;
	int count = 1;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj != meMons)
		{
			g_mons[count] = obj;
			count++;
		}
		return true;
	});
	for (int i = 1; i < count; i++)
	{
		for (int j = 1; i < count; j++)
		{
			if (g_mons[j]->Getteam() > g_mons[i]->Getteam())
			{
				Monster* mon = g_mons[j];
				g_mons[j] = g_mons[i];
				g_mons[i] = mon;
			}
		}
	}

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;
	

}
