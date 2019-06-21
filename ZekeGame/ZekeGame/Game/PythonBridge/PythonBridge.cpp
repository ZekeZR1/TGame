#include "stdafx.h"
#include <thread>
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
#include "../Monster/MonsterActionManeger.h"

#include "include/structmember.h"

#include "MVector3.h"

//#include "../GameData.h"
//#include "../Monster/Monster.h"
Monster* ME = nullptr;



//args = [team]
PyObject* GetAllBuddyData(PyObject* self, PyObject* args)
{
	int meTeam = PyLong_AsLong(PyTuple_GetItem(args, 0));
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* pDatas = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		//if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != meTeam)
			continue;
		PyObject* pData = PyList_New(12);

		PyList_SetItem(pData,0,PyLong_FromLong(mon->GetID()));
		PyList_SetItem(pData,1,PyLong_FromLong(mon->Getnum()));
		PyList_SetItem(pData,2,PyLong_FromLong(mon->Getteam()));
		PyList_SetItem(pData,3,PyLong_FromLong(mon->GetHP()));
		PyList_SetItem(pData,4,PyLong_FromLong(mon->GetMP()));


		PyObject* pPos = PyList_New(3);
		CVector3 pos = mon->Getpos();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 5, pPos);

		/////
		PyList_SetItem(pData, 6, PyFloat_FromDouble(mon->GetAttack()));
		PyList_SetItem(pData, 7, PyFloat_FromDouble(mon->GetExAttack()));
		PyList_SetItem(pData, 8, PyFloat_FromDouble(mon->GetDefense()));
		PyList_SetItem(pData, 9, PyFloat_FromDouble(mon->GetExDefense()));
		PyList_SetItem(pData, 10, PyFloat_FromDouble(mon->GetPspeed()));

		pPos = PyList_New(3);
		pos = mon->Getspeed();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 11, pPos);
		////

		PyList_SetItem(pDatas, count, pData);

		count++;
	}
	return pDatas;
}

//args = [team]
PyObject* GetAllEnemyData(PyObject* self, PyObject* args)
{
	int meTeam = PyLong_AsLong(PyTuple_GetItem(args, 0));
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* pDatas = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		//if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
		if (mon->Getnum() == g_meNum || mon->Getteam() == meTeam)
			continue;
		PyObject* pData = PyList_New(12);

		PyList_SetItem(pData, 0, PyLong_FromLong(mon->GetID()));
		PyList_SetItem(pData, 1, PyLong_FromLong(mon->Getnum()));
		PyList_SetItem(pData, 2, PyLong_FromLong(mon->Getteam()));
		PyList_SetItem(pData, 3, PyLong_FromLong(mon->GetHP()));
		PyList_SetItem(pData, 4, PyLong_FromLong(mon->GetMP()));

		PyObject* pPos = PyList_New(3);
		CVector3 pos = mon->Getpos();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 5, pPos);

		/////
		PyList_SetItem(pData, 6, PyFloat_FromDouble(mon->GetAttack()));
		PyList_SetItem(pData, 7, PyFloat_FromDouble(mon->GetExAttack()));
		PyList_SetItem(pData, 8, PyFloat_FromDouble(mon->GetDefense()));
		PyList_SetItem(pData, 9, PyFloat_FromDouble(mon->GetExDefense()));
		PyList_SetItem(pData, 10, PyFloat_FromDouble(mon->GetPspeed()));

		pPos = PyList_New(3);
		pos = mon->Getspeed();
		PyList_SetItem(pPos, 0, PyFloat_FromDouble(pos.x));
		PyList_SetItem(pPos, 1, PyFloat_FromDouble(pos.y));
		PyList_SetItem(pPos, 2, PyFloat_FromDouble(pos.z));

		PyList_SetItem(pData, 11, pPos);
		////

		PyList_SetItem(pDatas, count, pData);

		count++;
	}
	return pDatas;
}


//íáä‘ÇÃêîÇï‘Ç∑
static PyObject* GetBuddyCount(PyObject* self, PyObject* args)
{
	PyObject* bc = PyLong_FromLong(g_buddyCount);
	return bc;
}

//ÉGÉlÉ~Å[ÇÃêîÇï‘Ç∑
static PyObject* GetEnemyCount(PyObject* self, PyObject* args)
{
	PyObject* ec = PyLong_FromLong(g_enemyCount);
	return ec;
}


//args = [actions,num]
static PyObject* SetAction(PyObject* self, PyObject* args)
{
	PyObject* tup = PyTuple_GetItem(args, 0);
	int count = PyList_Size(tup);
	int num = PyLong_AsLong(PyTuple_GetItem(args, 1));
	Monster* mon = g_mons[num];
	MonsterActionManeger* mam = FindGO<MonsterActionManeger>("MAM");
	for (int i = 0; i < count; i++)
	{
		PyObject* pAct = PyList_GetItem(tup,i);
		int act = PyLong_AsLong(PyList_GetItem(pAct, 0));
		int tar = PyLong_AsLong(PyList_GetItem(pAct, 1));
		
		mon->AddAction(mam->LoadAction(act,tar));
	}
	PyObject* pnull = PyLong_FromLong(0);
	return pnull;
}


//moduleì‡ÇÃä÷êîÇΩÇø
static PyMethodDef methods[] =
{
	//{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},				//îpä¸ó\íË
	//{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},											//îpä¸ó\íË
	//{"GetMyMP",GetMyMP,METH_NOARGS,"Jibun no MP wo kaeshi masu."},											//îpä¸ó\íË
	//{"GetMyTeam",GetMyTeam,METH_NOARGS,"Jibun no Team wo kaeshi masu."},									//îpä¸ó\íË
	//{"GetMyNum",GetMyNum,METH_NOARGS,"Jibun no num wo kaeshi masu."},

	//{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},		//îpä¸ó\íË
	//{"GetAllBuddyNum",GetAllBuddyNum,METH_NOARGS,"Nakama zenin no num wo kaeshi masu."},					//îpä¸ó\íË
	{"GetAllBuddyData",GetAllBuddyData,METH_VARARGS,"Nakama zenin no data wo kaeshi masu."},

	//{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},		//îpä¸ó\íË
	//{"GetAllEnemyNum",GetAllEnemyNum,METH_NOARGS,"Teki zenin no num wo kaeshi masu."},						//îpä¸ó\íË
	//{"GetAllEnemyHP",GetAllEnemyHP,METH_NOARGS,"Teki zenin no HP wo kaeshi masu."},							//îpä¸ó\íË
	{"GetAllEnemyData",GetAllEnemyData,METH_VARARGS,"Teki zenin no data wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},

	{"SetAction",SetAction,METH_VARARGS,"action wo settei simasu"},

	{"sqrt",MSqrt,METH_VARARGS,"hehokon"},
	{NULL,NULL,0,NULL}
};

//module ñ{ëÃ
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
PyObject* thisModule = nullptr;

//moduleÇÃèâä˙âª
static PyObject* initModule(void)
{
	thisModule = PyModule_Create(&pModule);
	for (int i = 0; i < ActionID::enNumAction; i++)
	{
		size_t s = 0;
		const wchar_t* ws = GameData::GetActionName((ActionID)i);
		char st[256] = { 0 };
		wcstombs_s(&s, st, ws, wcslen(ws));
		PyModule_AddIntConstant(thisModule, st, i);
	}
	for (int i = 0; i < MonsterID::enNumMonster; i++)
	{
		PyModule_AddIntConstant(thisModule, GameData::GetMonsterNameMulti((MonsterID)i), i);
	}
	
	
	//ÉÇÉWÉÖÅ[ÉãÇ…ÉNÉâÉXí«â¡
	MVector3init();
	if (PyType_Ready(&MVector3Type) < 0)
		return NULL;
	Py_INCREF(&MVector3Type);
	PyModule_AddObject(thisModule, "Vector3", (PyObject*)&MVector3Type);

	return thisModule;
}


PythonBridge::PythonBridge()
{
	mam = FindGO<MonsterActionManeger>("MAM");
}



/*Ç±ÇÍÅIÅIÅI*/
//pythonÇé¿çsÇ∑ÇÈÉ]ÅB
void PythonBridge::py_exe(int num,int team,const char* file)
{
	g_meNum = num;
	g_meTeam = team;
	g_buddyCount = 0;
	g_enemyCount = 0;
	Monster* me;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj->Getnum() == num)
			me = obj;

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
	SetCurrentDirectory("Python36");
	PyImport_AppendInittab("SendGame", initModule);
	Py_InitializeEx(1);
	

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;

	//pName = PyUnicode_DecodeFSDefault(file);
	if (team != 256)
		//pName = PyUnicode_DecodeFSDefault("_MiddleExecute");
		pName = PyUnicode_DecodeFSDefault("PythonAIs._MiddleExecute");
	else
		pName = PyUnicode_DecodeFSDefault("PythonEnemyAIs._MiddleExecute");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	
	pFunction = PyObject_GetAttrString(pModule, "execute");

	pArgs = PyTuple_New(3);
	PyObject* pMenum = PyLong_FromLong(num);
	PyObject* pMeteam = PyLong_FromLong(team);
	PyObject* pFile = PyUnicode_FromString(file);
	PyTuple_SetItem(pArgs, 0, pMenum);
	PyTuple_SetItem(pArgs, 1, pMeteam);
	PyTuple_SetItem(pArgs, 2, pFile);

	pValue = PyObject_CallObject(pFunction, pArgs);

	int va = PyLong_AsLong(pValue);

	Py_DECREF(pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	if (pValue == NULL || va == 0)
	{
		if(pValue != NULL)
			Py_DECREF(pValue);

		SetCurrentDirectory("../");
		Py_Finalize();
		end = true;
		return;
	}

	Py_DECREF(pValue);
	Py_Finalize();


	SetCurrentDirectory("../");

	end = true;
}

Pyinit::Pyinit()
{
	//SetCurrentDirectory("Python36");
	/*PyImport_AppendInittab("SendGame", initModule);
	Py_InitializeEx(1);

	PyObject *pName, *pModule;
	pName = PyUnicode_DecodeFSDefault("PythonAIs.Threader");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	g_pFunction = PyObject_GetAttrString(pModule, "execute");*/
}

Pyinit::~Pyinit()
{
	//Py_Finalize();
	//SetCurrentDirectory("../");
}
