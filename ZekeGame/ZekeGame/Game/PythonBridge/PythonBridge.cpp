#include "stdafx.h"
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
//#include "../Monster/Monster.h"

//使用しているMonsterのポジションを返します
static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	Monster* mon;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject *x, *y, *z;
	x = PyFloat_FromDouble(mon->Getpos().x);
	y = PyFloat_FromDouble(mon->Getpos().y);
	z = PyFloat_FromDouble(mon->Getpos().z);


	PyObject* pos = PyList_New(3);
	PyList_SetItem(pos, 0, x);

	//pos = PyList_New(1);
	PyList_SetItem(pos, 1, y);

	//pos = PyList_New(2);
	PyList_SetItem(pos, 2, z);

	/*Py_DECREF(x);
	Py_DECREF(y);
	Py_DECREF(z);*/

	return pos;
}

static PyObject* GetMyHP(PyObject* self, PyObject* args)
{
	Monster* mon;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject* pHP = PyLong_FromLong(mon->GetHP());
	return pHP;
}

static PyObject* GetMyMP(PyObject* self, PyObject* args)
{
	Monster* mon;
	for (Monster* obj : g_mons)
	{
		if (obj->Getnum() == g_meNum)
		{
			mon = obj;
			break;
		}
	}
	PyObject* pMP = PyLong_FromLong(mon->GetMP());
	return pMP;
}

static PyObject* GetMyTeam(PyObject* self, PyObject* args)
{
	PyObject* pTeam = PyLong_FromLong(g_meTeam);
	return pTeam;
}

static PyObject* GetMyNum(PyObject* self, PyObject* args)
{
	PyObject* pNum = PyLong_FromLong(g_meNum);
	return pNum;
}

static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon->Getnum() == g_meNum || mon->Getteam() != 0)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyTuple_New(3);
		PyTuple_SetItem(pos, 0, x);

		PyTuple_SetItem(pos, 1, y);

		PyTuple_SetItem(pos, 2, z);

		PyTuple_SetItem(poss, count, pos);
		count++;
	}
	
	return poss;
}

static PyObject* GetAllBuddyNum(PyObject* self, PyObject* args)
{
	PyObject* nums = PyTuple_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon->Getnum() == g_meNum || mon->Getteam() != 0)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyTuple_SetItem(nums, count, num);
		count++;
	}

	return nums;
}

static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(g_enemyCount);

	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon->Getnum() == g_meNum || mon->Getteam() == 0)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyTuple_New(3);
		PyTuple_SetItem(pos, 0, x);

		PyTuple_SetItem(pos, 1, y);

		PyTuple_SetItem(pos, 2, z);

		PyTuple_SetItem(poss, count, pos);
		count++;
	}

	return poss;
}

//仲間の数を返す
static PyObject* GetBuddyCount(PyObject* self, PyObject* args)
{
	PyObject* bc = PyLong_FromLong(g_buddyCount);
	return bc;
}

//エネミーの数を返す
static PyObject* GetEnemyCount(PyObject* self, PyObject* args)
{
	PyObject* ec = PyLong_FromLong(g_enemyCount);
	return ec;
}

//module内の関数たち
static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},
	{"GetMyMP",GetMyMP,METH_NOARGS,"Jibun no MP wo kaeshi masu."},
	{"GetMyTeam",GetMyTeam,METH_NOARGS,"Jibun no Team wo kaeshi masu."},
	{"GetMyNum",GetMyNum,METH_NOARGS,"Jibun no num wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},
	{"GetAllBuddyNum",GetAllBuddyNum,METH_NOARGS,"Nakama zenin no num wo kaeshi masu."},

	{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},
	{NULL,NULL,0,NULL}
};

//module 本体
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

//moduleの初期化
static PyObject* initModule(void)
{
	return PyModule_Create(&pModule);
}


void PythonBridge::pbInit()
{
	int count = 0;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		g_mons[count] = obj;
		count++;
		return true;
	});
	for (int i = 1; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (g_mons[j]->Getteam() > g_mons[i]->Getteam())
			{
				Monster* mon = g_mons[j];
				g_mons[j] = g_mons[i];
				g_mons[i] = mon;
			}
		}
	}
}

//pythonを実行するゾ。
void PythonBridge::py_exe(int num,int team,char* file)
{
	if (file == NULL)
		return;
	g_meNum = num;
	g_meTeam = team;
	g_buddyCount = 0;
	g_enemyCount = 0;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj->Getteam() == team)
		{
			g_buddyCount++;
		}
		else
		{
			g_enemyCount++;
		}
		return true;
	});

	PyImport_AppendInittab("SendGame", initModule);

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;
	
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(file);
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	pFunction = PyObject_GetAttrString(pModule, "Brain");
	pArgs = PyTuple_New(0);
	pValue = PyObject_CallObject(pFunction, pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	int vl = PyList_Size(pValue);
	std::vector<float> actions;
	for (int i = 0; i < vl; i++)
	{
		actions.push_back(PyFloat_AsDouble(PyList_GetItem(pValue, i)));
	}

	Py_DECREF(pValue);
}
