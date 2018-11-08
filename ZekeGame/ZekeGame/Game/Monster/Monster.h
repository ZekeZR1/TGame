#pragma once
//#include "MonsterAI.h"
class MonsterAction;
class Monster:public GameObject
{
public:
	bool Start();
	void Update();
	void execute();

	enum en_State
	{
		NowLoading,
		Execute,
	};

	void SetpyFile(const char* st)
	{
		m_pyFile = st;
	}
	const char* GetpyFile()
	{
		return m_pyFile;
	}

	int GetHP()
	{
		return m_HP;
	}
	int GetMP()
	{
		return m_MP;
	}
	CVector3 Getpos()
	{
		return m_pos;
	}
	void Setpos(CVector3 v)
	{
		m_pos = v;
	}
	int Getteam()
	{
		return m_team;
	}
	int Getnum()
	{
		return m_num;
	}

	Monster* Getmon()
	{
		return this;
	}

protected:
	const char* m_pyFile = NULL;
	int m_ID = 0;
	int m_num = 0;
	int m_team = 0;
	std::vector<int> m_useAction;

	SkinModelRender* m_smr = nullptr;
	int m_HP = 0;
	int m_MP = 0;
	float m_gravity = 50.0f;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();

	std::vector<MonsterAction*> m_actions;
	en_State m_state = NowLoading;
};