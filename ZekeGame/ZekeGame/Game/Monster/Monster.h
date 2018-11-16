#pragma once
#include "../../Engine/character/CharacterController.h"

class MonsterAction;
class PythonBridge;
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

	void Knockback();

	void StartKnockback(CVector3 v);

	enum en_State
	{
		en_NowLoading,
		en_Execute,
		en_Dead,
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
	void Damage(int d)
	{
		m_HP -= d;
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
		return m_movespeed;
	}
	void Setspeed(CVector3 v)
	{
		m_oldmovespeed = m_movespeed;
		m_movespeed = v;
	}

	void Setiswalk(bool b)
	{
		m_iswalk = b;
	}
	int Getteam()
	{
		return m_team;
	}
	void Setteam(int t)
	{
		m_team = t;
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
	std::vector<MonsterAction*> Getactions()
	{
		return m_actions;
	}

	//アニメーションさせるときは必ずこいつらを使うこと。
	void anim_idle();
	void anim_walk();
	void anim_atack();
	void anim_defense();
	void anim_recovery();

	enum anim
	{
		en_idle,
		en_walk,
		en_atack,
		en_defense,
		en_recovery,
	};

protected:
	const char* m_pyFile = NULL;				//使うpythonファイルの名前
	int m_ID = 0;								//モンスターの種類を判断するためのID
	int m_num = 0;								//背番号みたいな感じ
	int m_team = 0;								//チーム番号

	CharacterController m_cc;					//キャラコン
	SkinModelRender* m_smr = nullptr;			//スキンモデルレンダー
	int m_HP = 0;								//HP
	int m_MP = 0;								//MP
	float m_gravity = 50.0f;					//重力
	CVector3 m_movespeed = CVector3::Zero();	//ムーブスピード
	CVector3 m_oldmovespeed = CVector3::Zero();	//古のムーブスピード
	bool m_iswalk = false;						//
	bool m_isKnockback = false;					//
	CVector3 m_vKnockback = CVector3::Zero();	//
	CVector3 m_vSubKnock = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();			//ポジション
	CQuaternion m_rot = CQuaternion::Identity();//回転

	PythonBridge* m_PB;
	std::vector<MonsterAction*> m_actions;		//使うアクション
	en_State m_state = en_NowLoading;

	int m_AnimNum = 0;							//アニメーションの個数

	float m_time = 0.0f;
};