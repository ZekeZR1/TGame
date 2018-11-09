#pragma once
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"
class MonsterAction;
//class CharacterController;
class Monster:public GameObject
{
public:
	//bool Start();
	void Update();
	void execute();

	void Move();
	void Turn();

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
	CVector3 Getspeed()
	{
		return m_speed;
	}
	void Setspeed(CVector3 v)
	{
		m_speed = v;
	}
	int Getteam()
	{
		return m_team;
	}
	int Getnum()
	{
		return m_num;
	}
	void Setnum(int num)
	{
		m_num = num;
	}

	Monster* Getmon()
	{
		return this;
	}

	void AddAction(MonsterAction* ma);

protected:
	const char* m_pyFile = NULL;
	int m_ID = 0;
	int m_num = 0;
	int m_team = 0;
	std::vector<int> m_useAction;

	CharacterController m_cc;
	SkinModelRender* m_smr = nullptr;
	int m_HP = 0;
	int m_MP = 0;
	float m_gravity = 50.0f;
	CVector3 m_speed = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();

	std::vector<MonsterAction*> m_actions;
	en_State m_state = NowLoading;
};