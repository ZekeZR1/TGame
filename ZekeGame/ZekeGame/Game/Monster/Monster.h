#pragma once
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"
class MonsterAction;
class PythonBridge;
//class CharacterController;
class Monster:public GameObject
{
public:
	~Monster();

	bool Start();
	void Update();

	//Monsterのアクションを実行する関数
	void execute();

	//移動するときに使う関数
	void Move();

	//回転するときに使う関数
	void Turn();


	enum en_State
	{
		en_NowLoading,
		en_Execute,
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
		m_oldspeed = m_speed;
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
	const char* m_pyFile = NULL;				//使うpythonファイルの名前
	int m_ID = 0;								//モンスターの種類を判断するためのID
	int m_num = 0;								//背番号みたいな感じ
	int m_team = 0;								//チーム番号
	//std::vector<int> m_useAction;

	CharacterController m_cc;					//キャラコン
	SkinModelRender* m_smr = nullptr;			//スキンモデルレンダー
	int m_HP = 0;								//HP
	int m_MP = 0;								//MP
	float m_gravity = 50.0f;					//重力
	CVector3 m_speed = CVector3::Zero();		//ムーブスピード
	CVector3 m_oldspeed = CVector3::Zero();		//古のムーブスピード
	CVector3 m_pos = CVector3::Zero();			//ポジション
	CQuaternion m_rot = CQuaternion::Identity();//回転

	PythonBridge* m_PB;
	std::vector<MonsterAction*> m_actions;		//使うアクション
	en_State m_state = en_NowLoading;
};