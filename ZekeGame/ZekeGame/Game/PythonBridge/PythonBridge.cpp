#include "stdafx.h"
#include <thread>
#include "PythonBridge.h"
#include "../Monster/MonsterAction.h"
#include "../Monster/MonsterActionManeger.h"

#include "include/structmember.h"

#include "../GameLog/GameLog.h"


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

//àÍî‘âìÇ¢ÉÇÉìÉXÉ^Å[ÇíTÇ∑
static PyObject* GetFarMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len=0;
	int top=0;
	int team=0;
	for (auto mon : g_mons)
	{
		
		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		if (mnum == num)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l > len)
		{
			len = l;
			top = mnum;
			team = mon->Getteam();
		}
	}
	MMonster* mmon=NULL;
	if (mgameData->me->team == team)
	{
		int i = PyList_Size((PyObject*)mgameData->Buddys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	else
	{
		int i = PyList_Size((PyObject*)mgameData->Enemys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}

//àÍî‘ãﬂÇ¢ÉÇÉìÉXÉ^Å[ÇíTÇ∑
static PyObject* GetNeerMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len = 999999999;
	int top = 0;
	int team;
	for (auto mon : g_mons)
	{

		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		if (mnum == num)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l < len)
		{
			len = l;
			top = mnum;
			team = mon->Getteam();
		}
	}
	MMonster* mmon;
	if (mgameData->me->team == team)
	{
		int i = PyList_Size((PyObject*)mgameData->Buddys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	else
	{
		int i = PyList_Size((PyObject*)mgameData->Enemys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				Py_INCREF(mmon);
				return (PyObject*)mmon;
			}
		}
	}
	
	
}

//àÍî‘âìÇ¢íáä‘ÇíTÇ∑
static PyObject* GetBuddyFarMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len = 0;
	int top = 0;
	int team;
	for (auto mon : g_mons)
	{

		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		team = mon->Getteam();
		if (mnum == num || team != mgameData->me->team)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l > len)
		{
			len = l;
			top = mnum;
			
		}
	}
	MMonster* mmon;
	int i = PyList_Size((PyObject*)mgameData->Buddys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			Py_INCREF(mmon);
			return (PyObject*)mmon;
		}
	}
	
}
//àÍî‘ãﬂÇ¢íáä‘ÇíTÇ∑
static PyObject* GetBuddyNeerMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len = 999999999;
	int top = 0;
	int team;
	for (auto mon : g_mons)
	{

		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		team = mon->Getteam();
		if (mnum == num || team != mgameData->me->team)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l < len)
		{
			len = l;
			top = mnum;

		}
	}
	MMonster* mmon;
	int i = PyList_Size((PyObject*)mgameData->Buddys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			Py_INCREF(mmon);
			return (PyObject*)mmon;
		}
	}
	
	
}

//àÍî‘âìÇ¢ìGÇíTÇ∑
static PyObject* GetEnemyFarMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len = 0;
	int top = 0;
	int team;
	for (auto mon : g_mons)
	{

		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		team = mon->Getteam();
		if (mnum == num || team == mgameData->me->team)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l > len)
		{
			len = l;
			top = mnum;

		}
	}
	MMonster* mmon;
	int i = PyList_Size((PyObject*)mgameData->Buddys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			Py_INCREF(mmon);
			return (PyObject*)mmon;
		}
	}
	
	
}
//àÍî‘ãﬂÇ¢ìGÇíTÇ∑
static PyObject* GetEnemyNeerMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	CVector3 pos = MVector3ToVector3(mgameData->me->position);
	float len = 999999999;
	int top = 0;
	int team;
	for (auto mon : g_mons)
	{

		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		team = mon->Getteam();
		if (mnum == num || team == mgameData->me->team)
			continue;
		float l = (mon->Getpos() - pos).Length();
		if (l < len)
		{
			len = l;
			top = mnum;

		}
	}
	MMonster* mmon;
	int i = PyList_Size((PyObject*)mgameData->Enemys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			Py_INCREF(mmon);
			return (PyObject*)mmon;
		}
	}
	
	
}

//àÍî‘HPÇÃëΩÇ¢ÉÇÉìÉXÉ^Å[ÇíTÇ∑
static PyObject* GetHighHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 0;
	int top = 0;
	int team = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp > topHP)
		{
			topHP = hp;
			top = mnum;
			team = mon->Getteam();
		}
	}
	MMonster* mmon = NULL;
	if (mgameData->me->team == team)
	{
		int i = PyList_Size((PyObject*)mgameData->Buddys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	else
	{
		int i = PyList_Size((PyObject*)mgameData->Enemys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}
//àÍî‘HPÇÃè≠Ç»Ç¢ÉÇÉìÉXÉ^Å[ÇíTÇ∑
static PyObject* GetRowHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 9999999999;
	int top = 0;
	int team = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp < topHP)
		{
			topHP = hp;
			top = mnum;
			team = mon->Getteam();
		}
	}
	MMonster* mmon = NULL;
	if (mgameData->me->team == team)
	{
		int i = PyList_Size((PyObject*)mgameData->Buddys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	else
	{
		int i = PyList_Size((PyObject*)mgameData->Enemys);
		while (--i != -1)
		{
			MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
			if (mon->num == top)
			{
				mmon = mon;
				break;
			}
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}

//àÍî‘HPÇÃëΩÇ¢íáä‘ÇíTÇ∑
static PyObject* GetBuddyHighHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 0;
	int top = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() !=mgameData->me->team)
			continue;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp > topHP)
		{
			topHP = hp;
			top = mnum;
		}
	}
	MMonster* mmon = NULL;
	int i = PyList_Size((PyObject*)mgameData->Buddys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			break;
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}
//àÍî‘HPÇÃè≠Ç»Ç¢íáä‘ÇíTÇ∑
static PyObject* GetBuddyRowHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 9999999999;
	int top = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() != mgameData->me->team)
			continue;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp < topHP)
		{
			topHP = hp;
			top = mnum;
		}
	}
	MMonster* mmon = NULL;
	int i = PyList_Size((PyObject*)mgameData->Buddys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Buddys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			break;
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}

//àÍî‘HPÇÃëΩÇ¢ìGÇíTÇ∑
static PyObject* GetEnemyHighHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 0;
	int top = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == mgameData->me->team)
			continue;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp > topHP)
		{
			topHP = hp;
			top = mnum;
		}
	}
	MMonster* mmon = NULL;
	int i = PyList_Size((PyObject*)mgameData->Enemys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			break;
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}
//àÍî‘HPÇÃè≠Ç»Ç¢ìGÇíTÇ∑
static PyObject* GetEnemyRowHPMonster(PyObject* self, PyObject* args)
{
	int num = pData()->Getnum();
	MGameData* mgameData = pData()->GetgameData();
	int topHP = 9999999999;
	int top = 0;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == mgameData->me->team)
			continue;
		int mnum = mon->Getnum();
		int hp = mon->GetHP();
		if (hp < topHP)
		{
			topHP = hp;
			top = mnum;
		}
	}
	MMonster* mmon = NULL;
	int i = PyList_Size((PyObject*)mgameData->Enemys);
	while (--i != -1)
	{
		MMonster* mon = (MMonster*)mgameData->Enemys->ob_item[i];
		if (mon->num == top)
		{
			mmon = mon;
			break;
		}
	}
	Py_INCREF(mmon);
	return (PyObject*)mmon;
}




/*
éwíËÇµÇΩIDÇÃíáä‘ÇíTÇ∑
arg: monID
*/
static PyObject* FindBuddyMonster(PyObject* self, PyObject* args)
{
	int monID = PyLong_AsLong(PyTuple_GetItem(args, 0));
	int num = 0;
	int team = pData()->Getteam();
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() != team)
			continue;
		if (mon->GetID() == monID)
		{
			num = mon->Getnum();
			break;
		}
	}
	PyObject* mon = Py_None;
	PyListObject* enemys = pData()->GetgameData()->Enemys;
	int i = PyList_Size((PyObject*)enemys);
	while (--i != -1)
	{
		MMonster* m = (MMonster*)(enemys->ob_item[i]);
		if (m->num == num)
		{
			mon = (PyObject*)m;
			Py_INCREF(mon);
			break;
		}
	}
	return mon;
}
/*
éwíËÇµÇΩIDÇÃìGíTÇ∑
arg: monID
*/
static PyObject* FindEnemyMonster(PyObject* self, PyObject* args)
{
	int monID = PyLong_AsLong(PyTuple_GetItem(args, 0));
	int num = 0;
	int team = pData()->Getteam();
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == team)
			continue;
		if (mon->GetID() == monID)
		{
			num = mon->Getnum();
			break;
		}
	}
	PyObject* mon = Py_None;
	PyListObject* enemys = pData()->GetgameData()->Enemys;
	int i = PyList_Size((PyObject*)enemys);
	while (--i != -1)
	{
		MMonster* m = (MMonster*)(enemys->ob_item[i]);
		if (m->num == num)
		{
			mon = (PyObject*)m;
			Py_INCREF(mon);
			break;
		}
	}
	return mon;
}

/*
éwíËÇµÇΩIDÇÃàÍívÇ∑ÇÈÇ∑Ç◊ÇƒÇÃìGÇíTÇ∑
arg: monID
*/
static PyObject* FindEnemyMonsters(PyObject* self, PyObject* args)
{
	int monID = PyLong_AsLong(PyTuple_GetItem(args, 0));
	int num[6] = {99};
	int numc = 0;
	int team = pData()->Getteam();
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == team)
			continue;
		if (mon->GetID() == monID)
		{
			num[numc++] = mon->Getnum();
		}
	}
	int size = numc;
	PyObject* mons = PyList_New(0);
	PyListObject* enemys = pData()->GetgameData()->Enemys;
	int i = PyList_Size((PyObject*)enemys);
	while (--i != -1)
	{
		MMonster* m = (MMonster*)(enemys->ob_item[i]);
		while (--numc != -1)
		{
			if (m->num == num[numc])
			{
				PyList_Append(mons, (PyObject*)m);
				numc = size;
			}
		}
	}
	return mons;
}
/*
éwíËÇµÇΩIDÇÃàÍívÇ∑ÇÈÇ∑Ç◊ÇƒÇÃíáä‘ÇíTÇ∑
arg: monID
*/
static PyObject* FindBuddyMonsters(PyObject* self, PyObject* args)
{
	int monID = PyLong_AsLong(PyTuple_GetItem(args, 0));
	int num[6] = { 99 };
	int numc = 0;
	int team = pData()->Getteam();
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() != team)
			continue;
		if (mon->GetID() == monID)
		{
			num[numc++] = mon->Getnum();
		}
	}
	int size = numc;
	PyObject* mons = PyList_New(0);
	PyListObject* enemys = pData()->GetgameData()->Buddys;
	int i = PyList_Size((PyObject*)enemys);
	while (--i != -1)
	{
		MMonster* m = (MMonster*)(enemys->ob_item[i]);
		while (--numc != -1)
		{
			if (m->num == num[numc])
			{
				PyList_Append(mons, (PyObject*)m);
				numc = size;
			}
		}
	}
	return mons;
}


/*
meÇ…ÉAÉNÉVÉáÉìÇí«â¡
*/
static PyObject* addAction(PyObject* self, PyObject* args)
{
	
	PyObject* tar = PyTuple_GetItem(args, 0);
	int act = PyLong_AsLong(PyTuple_GetItem(args, 1));
	
	Monster* mon = NULL;
	Monster* target = NULL;
	for (auto m : g_mons)
	{
		if (m == NULL)
			break;
		if (pData()->Getnum() == m->Getnum())
		{
			mon = m;
			break;
		}
	}
	if(tar->ob_type==&MMonsterType)
		mon->AddAction(MonsterActionManeger::LoadAction(act,((MMonster*)tar)->num));
	else
		mon->AddAction(MonsterActionManeger::LoadAction(act,PyLong_AsLong(tar)));
	return &_Py_NoneStruct;
}

static PyObject* MMprint(PyObject* self, PyObject* args)
{
	wchar_t ws[255] = {0};
	PyObject* uc = PyTuple_GetItem(args, 0);
	int size = PyUnicode_AsWideChar(uc, ws, PyUnicode_GetLength(uc));

	std::wstring str = ws;
	MMprint(str);

	return Py_None;
}

//moduleì‡ÇÃä÷êîÇΩÇø
static PyMethodDef methods[] =
{
	{"GetAllBuddyData",GetAllBuddyData,METH_VARARGS,"Nakama zenin no data wo kaeshi masu."},

	{"GetAllEnemyData",GetAllEnemyData,METH_VARARGS,"Teki zenin no data wo kaeshi masu."},

	{"GetBuddyCount",GetBuddyCount,METH_NOARGS,"mikata no kazu wo kaeshi masu."},
	{"GetEnemyCount",GetEnemyCount,METH_NOARGS,"teki no kazu wo kaeshi masu."},

	{"SetAction",SetAction,METH_VARARGS,"action wo settei simasu"},

	{"sqrt",MSqrt,METH_VARARGS,"hehokon"},

	{"GetFarMonster",GetFarMonster,METH_NOARGS,"hehokon"},
	{"GetNeerMonster",GetNeerMonster,METH_NOARGS,"hehokon"},
	{"GetBuddyFarMonster",GetBuddyFarMonster,METH_NOARGS,"hehokon"},
	{"GetEnemyFarMonster",GetEnemyFarMonster,METH_NOARGS,"hehokon"},
	{"GetBuddyNeerMonster",GetBuddyNeerMonster,METH_NOARGS,"hehokon"},
	{"GetEnemyNeerMonster",GetEnemyNeerMonster,METH_NOARGS,"hehokon"},
	
	{"GetHighHPMonster",GetHighHPMonster,METH_NOARGS,"hehokon"},
	{"GetBuddyHighHPMonster",GetBuddyHighHPMonster,METH_NOARGS,"hehokon"},
	{"GetEnemyHighHPMonster",GetEnemyHighHPMonster,METH_NOARGS,"hehokon"},

	{"GetLowHPMonster",GetRowHPMonster,METH_NOARGS,"hehokon"},
	{"GetBuddyLowHPMonster",GetBuddyRowHPMonster,METH_NOARGS,"hehokon"},
	{"GetEnemyLowHPMonster",GetEnemyRowHPMonster,METH_NOARGS,"hehokon"},

	{"FindBuddyMonster",FindBuddyMonster,METH_VARARGS,"hehokon"},
	{"FindEnemyMonster",FindEnemyMonster,METH_VARARGS,"hehokon"},
	{"FindBuddyMonsters",FindBuddyMonsters,METH_VARARGS,"hehokon"},
	{"FindEnemyMonsters",FindEnemyMonsters,METH_VARARGS,"hehokon"},

	{"addAction",addAction,METH_VARARGS,"hehokon"},
	{"MMprint",MMprint,METH_VARARGS,"hehokon"},
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

	MMonsterInit();
	if (PyType_Ready(&MMonsterType) < 0)
		return NULL;
	Py_INCREF(&MMonsterType);
	PyModule_AddObject(thisModule, "Monster", (PyObject*)& MMonsterType);

	MGameDataInit();
	if (PyType_Ready(&MGameDataType) < 0)
		return NULL;
	Py_INCREF(&MGameDataType);
	PyModule_AddObject(thisModule, "GameData", (PyObject*)& MGameDataType);

	//MGameData* gameData = (MGameData*)MGameDataType.tp_new(&MGameDataType,NULL,NULL);
	////MGameData* gameData = PyObject_GC_New(MGameData, &MGameDataType);
	////PyObject_Init((PyObject*)gameData, &MGameDataType);

	//PyModule_AddObject(thisModule, "gameData", (PyObject*)gameData);
	//
	//PyObject* arg = PyTuple_New(2);
	//PyTuple_SetItem(arg, 0, PyLong_FromLong(pData()->Getnum()));
	//PyTuple_SetItem(arg, 1, PyLong_FromLong(pData()->Getteam()));
	//MGameDataType.tp_init((PyObject*)gameData, arg, NULL);
	//Py_XDECREF(arg);

	/*MGameData* gameData = (MGameData*)MGameDataType.tp_new(&MGameDataType, NULL, NULL);
	PyModule_AddObject(thisModule, "gameData", (PyObject*)gameData);
	pData()->SetgameData(gameData);*/

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
	pData()->Setnum(num);
	pData()->Setteam(team);
	Monster* me;
	for (auto mon : g_mons)
	{
		if (mon == nullptr)
			break;
		if (mon->Getnum() == num)
			me = mon;

		if (mon->Getteam() == team)
		{
			g_buddyCount++;
		}
		else
		{
			g_enemyCount++;
		}
	}
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
		//end = true;
		return;
	}

	Py_DECREF(pValue);
	
	Py_Finalize();
	SetCurrentDirectory("../");
	//end = true;
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
