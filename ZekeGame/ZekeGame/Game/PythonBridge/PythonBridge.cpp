#include "stdafx.h"
#include <thread>
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
#include "../Monster/MonsterActionManeger.h"

//#include "../GameData.h"
//#include "../Monster/Monster.h"
Monster* ME = nullptr;

//使用しているMonsterのポジションを返します
//廃棄予定
static PyObject* GetMyPosition(PyObject* self,PyObject* args)
{
	Monster* mon = nullptr;
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

//廃棄予定
static PyObject* GetMyHP(PyObject* self, PyObject* args)
{
	Monster* mon = nullptr;
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

//廃棄予定
static PyObject* GetMyMP(PyObject* self, PyObject* args)
{
	Monster* mon = nullptr;
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

//廃棄予定
static PyObject* GetMyTeam(PyObject* self, PyObject* args)
{
	PyObject* pTeam = PyLong_FromLong(g_meTeam);
	return pTeam;
}

//廃棄予定
static PyObject* GetMyNum(PyObject* self, PyObject* args)
{
	PyObject* pNum = PyLong_FromLong(g_meNum);
	return pNum;
}

//未使用
static PyObject* GetMonster(PyObject* self, PyObject* args)
{
	int num = PyLong_AsLong(PyTuple_GetItem(args, 0));

	Monster* mon = g_mons[num];

}

//廃棄予定
static PyObject* GetAllBuddyPosition(PyObject* self, PyObject* args)
{
	//PyObject* poss = PyList_New(g_buddyCount-1);
	PyObject* poss = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyList_New(3);
		PyList_SetItem(pos, 0, x);

		PyList_SetItem(pos, 1, y);

		PyList_SetItem(pos, 2, z);

		PyList_SetItem(poss, count, pos);
		count++;
	}
	
	return poss;
}

//廃棄予定
static PyObject* GetAllBuddyNum(PyObject* self, PyObject* args)
{
	//PyObject* nums = PyList_New(g_buddyCount-1);
	PyObject* nums = PyList_New(g_buddyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (/*mon->Getnum() == g_meNum ||*/ mon->Getteam() != g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyList_SetItem(nums, count, num);
		count++;
	}

	return nums;
}

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


//廃棄予定
static PyObject* GetAllEnemyPosition(PyObject* self, PyObject* args)
{
	PyObject* poss = PyList_New(g_enemyCount);

	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject *x, *y, *z;
		x = PyLong_FromDouble(mon->Getpos().x);
		y = PyLong_FromDouble(mon->Getpos().y);
		z = PyLong_FromDouble(mon->Getpos().z);

		PyObject* pos = PyList_New(3);
		PyList_SetItem(pos, 0, x);

		PyList_SetItem(pos, 1, y);

		PyList_SetItem(pos, 2, z);

		PyList_SetItem(poss, count, pos);
		count++;
	}

	return poss;
}

//廃棄予定
static PyObject* GetAllEnemyNum(PyObject* self, PyObject* args)
{
	PyObject* nums = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->Getnum());

		PyList_SetItem(nums, count, num);
		count++;
	}

	return nums;
}
//廃棄予定
static PyObject* GetAllEnemyHP(PyObject* self, PyObject* args)
{
	PyObject* pHPs = PyList_New(g_enemyCount);
	int count = 0;
	for (Monster* mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getnum() == g_meNum || mon->Getteam() == g_meTeam)
			continue;
		PyObject* num = PyLong_FromLong(mon->GetHP());

		PyList_SetItem(pHPs, count, num);
		count++;
	}
	return pHPs;
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

//module内の関数たち
static PyMethodDef methods[] =
{
	{"GetMyPosition",GetMyPosition,METH_NOARGS,"Jibun no position wo tuple de kaeshi masu."},				//廃棄予定
	{"GetMyHP",GetMyHP,METH_NOARGS,"Jibun no HP wo kaeshi masu."},											//廃棄予定
	{"GetMyMP",GetMyMP,METH_NOARGS,"Jibun no MP wo kaeshi masu."},											//廃棄予定
	{"GetMyTeam",GetMyTeam,METH_NOARGS,"Jibun no Team wo kaeshi masu."},									//廃棄予定
	{"GetMyNum",GetMyNum,METH_NOARGS,"Jibun no num wo kaeshi masu."},

	{"GetAllBuddyPosition",GetAllBuddyPosition,METH_NOARGS,"Nakama zenin no position wo kaeshi masu."},		//廃棄予定
	{"GetAllBuddyNum",GetAllBuddyNum,METH_NOARGS,"Nakama zenin no num wo kaeshi masu."},					//廃棄予定
	{"GetAllBuddyData",GetAllBuddyData,METH_VARARGS,"Nakama zenin no data wo kaeshi masu."},

	{"GetAllEnemyPosition",GetAllEnemyPosition,METH_NOARGS,"Teki zenin no position wo kaeshi masu."},		//廃棄予定
	{"GetAllEnemyNum",GetAllEnemyNum,METH_NOARGS,"Teki zenin no num wo kaeshi masu."},						//廃棄予定
	{"GetAllEnemyHP",GetAllEnemyHP,METH_NOARGS,"Teki zenin no HP wo kaeshi masu."},							//廃棄予定
	{"GetAllEnemyData",GetAllEnemyData,METH_VARARGS,"Teki zenin no data wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},

	{"SetAction",SetAction,METH_VARARGS,"action wo settei simasu"},
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
PyObject* thisModule = nullptr;

//moduleの初期化
static PyObject* initModule(void)
{
	
	return thisModule;
}


PythonBridge::PythonBridge()
{
	mam = FindGO<MonsterActionManeger>("MAM");
}

void PythonBridge::Update()
{/*
	for (int i = 0;i < threads.size();i++)
	{
		if (comp[i])
		{
			threads[i]->detach();
			auto ite = std::find(threads.begin(), threads.end(), threads[i]);
			threads.erase(ite);
		}
	}*/
	if (pTS != nullptr && end)
	{
		PyEval_RestoreThread(pTS);
		////PyEval_ReleaseThread(pTS);
		//Py_Finalize();
		end = false;
	}
}

//使っていない
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

//使っていない
bool py_exe(int num, int team, const char* file)
{
	std::unique_ptr<std::thread> th = nullptr;
	th.reset(new std::thread([&]
	{
		MonsterActionManeger* mam = FindGO<MonsterActionManeger>("MAM");
		if (file == NULL)
			return;
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

		/*for (int i = 0; i < MonsterID::enNumMonster; i++)
		{
			PyObject* v;
			v = PyLong_FromLong(i);

			
		}*/

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
		if (vl == 0)
		{
			Py_DECREF(pValue);
			SetCurrentDirectory("../");
			Py_Finalize();
			return;
		}
		//std::vector<int[2]> actions;
		for (int i = 0; i < vl; i++)
		{
			int action[2];
			action[0] = PyLong_AsLong(PyList_GetItem(PyList_GetItem(pValue, i), 0));
			action[1] = PyLong_AsLong(PyList_GetItem(PyList_GetItem(pValue, i), 1));
			me->AddAction(mam->LoadAction(action[0], action[1]));
		}

		Py_DECREF(pValue);

		SetCurrentDirectory("../");
		Py_Finalize();
	}));
	return true;
}

/*これ！！！*/
//pythonを実行するゾ。
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

	thisModule = PyModule_Create(&pModule);
	for (int i = 0; i < ActionID::enNumAction; i++)
	{
		size_t s = 0;
		const wchar_t* ws = GameData::GetActionName((ActionID)i);
		char st[256] = {0};
		wcstombs_s(&s,st, ws, wcslen(ws));
		PyModule_AddIntConstant(thisModule, st,i);
	}
	for (int i = 0; i < MonsterID::enNumMonster; i++)
	{
		PyModule_AddIntConstant(thisModule, GameData::GetMonsterNameMulti((MonsterID)i), i);
	}
	PyTypeObject* pNclass;
	PyMethodDef pMet;
	//pMet.

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

void PythonBridge::AddExe(int num, int team, const char * file)
{
	ExeData ed = { num,team,file };
	m_exeDatalist.push_back(ed);
}

PyObject* g_pFunction;
// thread 使う　時の　関数
void PythonBridge::py_exeEX(int num, int team, const char * file)
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


	/*PyEval_InitThreads();

	th.reset(new std::thread([=]
	{
		PyGILState_STATE GILState;
		GILState = PyGILState_Ensure();*/
	PyImport_AppendInittab("SendGame", initModule);
	Py_InitializeEx(1);

	PyObject *pName, *pModule, *pFunction, *pArgs, *pValue;

	//pName = PyUnicode_DecodeFSDefault(file);

	pName = PyUnicode_DecodeFSDefault("PythonAIs.testBrain");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	//pFunction = PyObject_GetAttrString(pModule, "execute");

	pFunction = PyObject_GetAttrString(pModule, "Brain");

	pArgs = PyTuple_New(3);
	PyObject* pMenum = PyLong_FromLong(num);
	PyObject* pMeteam = PyLong_FromLong(team);
	PyObject* pFile = PyUnicode_FromString(file);
	PyTuple_SetItem(pArgs, 0, pMenum);
	PyTuple_SetItem(pArgs, 1, pMeteam);
	PyTuple_SetItem(pArgs, 2, pFile);

 	//pValue = PyObject_CallObject(g_pFunction, pArgs);
 	pValue = PyObject_CallObject(pFunction, pArgs);


	Py_DECREF(pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunction);

	if (pValue == NULL)
	{
		SetCurrentDirectory("../");
		Py_Finalize();
		//PyGILState_Release(GILState);
		end = true;
		return;
	}
	int vl = PyList_Size(pValue);
	if (vl == 0)
	{
		Py_DECREF(pValue);
		
		Py_Finalize();
		//PyGILState_Release(GILState);
		end = true;
		return;
	}

	Py_DECREF(pValue);
	Py_Finalize();
	

	SetCurrentDirectory("../");

	//PyGILState_Release(GILState);
	end = true;
	//}));

	//pTS = PyEval_SaveThread();
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
