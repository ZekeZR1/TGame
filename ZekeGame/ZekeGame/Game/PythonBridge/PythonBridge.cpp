#include "stdafx.h"
#include "PythonBridge.h"
//#include "../Monster/Monster.h"

//使用しているMonsterのポジションを返します
static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	PyObject *x, *y, *z;
	x = PyFloat_FromDouble(g_mons[0]->Getpos().x);
	y = PyFloat_FromDouble(g_mons[0]->Getpos().y);
	z = PyFloat_FromDouble(g_mons[0]->Getpos().z);


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
	PyObject* pHP = PyLong_FromLong(g_mons[0]->GetHP());
	return pHP;
}

static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(buddyCount);
	for (int i = 0; i < buddyCount; i++)
	{
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(g_mons[i]->Getpos().x);
		y = PyLong_FromDouble(g_mons[i]->Getpos().y);
		z = PyLong_FromDouble(g_mons[i]->Getpos().z);

		PyObject* pos = PyTuple_New(3);
		PyTuple_SetItem(pos, 0, x);

		//pos = PyTuple_New(1);
		PyTuple_SetItem(pos, 1, y);

		//pos = PyTuple_New(2);
		PyTuple_SetItem(pos, 2, z);

		//poss = PyTuple_New(i);
		PyTuple_SetItem(poss, i, pos);

		/*Py_DECREF(x);
		Py_DECREF(y);
		Py_DECREF(z);
		Py_DECREF(pos);*/
	}
	
	return poss;
}

static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyTuple_New(enemyCount);
	for (int i = buddyCount; i < buddyCount+enemyCount; i++)
	{
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(g_mons[i]->Getpos().x);
		y = PyLong_FromDouble(g_mons[i]->Getpos().y);
		z = PyLong_FromDouble(g_mons[i]->Getpos().z);

		PyObject* pos = PyTuple_New(3);
		PyTuple_SetItem(pos, 0, x);

		//pos = PyTuple_New(1);
		PyTuple_SetItem(pos, 1, y);

		//pos = PyTuple_New(2);
		PyTuple_SetItem(pos, 2, z);

		//poss = PyTuple_New(i);
		PyTuple_SetItem(poss, i, pos);

		/*Py_DECREF(x);
		Py_DECREF(y);
		Py_DECREF(z);
		Py_DECREF(pos);*/
	}

	return poss;
}

//仲間の数を返す
static PyObject* GetBuddyCount(PyObject* self, PyObject* args)
{
	PyObject* bc = PyLong_FromLong(buddyCount);
	return bc;
}

//エネミーの数を返す
static PyObject* GetEnemyCount(PyObject* self, PyObject* args)
{
	PyObject* ec = PyLong_FromLong(enemyCount);
	return ec;
}

//module内の関数たち
static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},
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


//pythonを実行するゾ。
void PythonBridge::py_exe(Monster* meMons)
{
	g_mons[0] = meMons;
	int count = 1;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj == nullptr)
			return true;
		if (obj != meMons)
		{
			g_mons[count] = obj;
			count++;
			if (obj->Getteam() == 0)
			{
				buddyCount++;
			}
			else
			{
				enemyCount++;
			}
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

	PyImport_AppendInittab("SendGame", initModule);

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;
	
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault("testBrain");
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
