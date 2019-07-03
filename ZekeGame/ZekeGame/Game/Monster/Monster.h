#pragma once
#include "../../Engine/character/CharacterController.h"

#include "../VisualScriptAI/VisualScriptAI.h"

class MonsterAction;
class MonsterEffect;
class MonsterActionList;
class MonsterMarker;
class PythonBridge;
class ACTEffectGrant;
enum ActionID;

class Monster:public GameObject
{
public:
	~Monster();

	struct MonsterInitParam {
		float HP;
		float MP;
		float DefencePow;
		float ExDefensePow;
		float AttackPow;
		float ExAttackPow;
		float Speed;
		float Radius;
		float Height;
		SkinModelRender* ModelRender;
		int NumAnimation;
	};

	void init(float HP, float MP,float Defence, float ExDefense, 
		float Attack,float ExAttack, float speed, 
					float radius, float height, SkinModelRender* smr, 
		int animnum);

	void init(MonsterInitParam param);

	void SuddenDeath();

	bool Start() override final;
	void Update() override final;

	void SetUseAction(ActionID* ua,int size);
	ActionID* GetUseAction()
	{
		return m_UseAction;
	}

	//Monsterのアクションを実行する関数
	void execute();

	//移動するときに使う関数
	void Move();

	//回転するときに使う関数
	void Turn();

	void TurnEx();

	void receiveDamage();

	//ノックバック時に使う関数
	void Knockback();

	//ノックバックの始まり
	//v: ノックバックするベクトル
	void StartKnockback(CVector3 v);

	void SetKnockback(CVector3 v);

	//状態
	enum en_State
	{
		en_NowLoading,
		en_Execute,
		en_Dead,
	};
	
	int GetState()
	{
		return m_state;
	}


	enum AbnormalState
	{
		abNull,		//None
		abPoison,	//毒
		abStan,		//スタン
		abBurn,		//やけど
		abCC,		//移動妨害
	};

	//状態異常の設定
	//abn: enum
	//void SetAbnormalState(int abn)
	//{
	//	//m_abnormalState = (AbnormalState)abn;
	//	m_abnormalStates.push_back((AbnormalState)abn);
	//}
	void SetAbnormalState(ACTEffectGrant* abn)
	{
		m_abnormalStates.push_back(abn);
	}

	/*void ClearAbnormalState(int abn)
	{
		std::vector<AbnormalState>::iterator ite;
		ite = std::find(m_abnormalStates.begin(), m_abnormalStates.end(), (AbnormalState)abn);
		m_abnormalStates.erase(ite);

	}*/
	void ClearAbnormalState(ACTEffectGrant* abn)
	{
		if (!m_abnormalStates.size()) return;
		if (m_abnormalStates.size() == 1) {
			m_abnormalStates.clear();
		}
		else {
			m_abnormalStates.erase(remove(m_abnormalStates.begin(), m_abnormalStates.end(), abn));
		}
		//std::vector<ACTEffectGrant*>::iterator ite;
		//ite = std::find(m_abnormalStates.begin(), m_abnormalStates.end(), abn);
		//m_abnormalStates.erase(ite);
	}
	
	//状態異常の取得
	//return 状態異常
	/*std::vector<AbnormalState> GetAbnormalState()
	{
		return m_abnormalStates;
	}*/
	std::vector<ACTEffectGrant*> GetAbnormalState()
	{
		return m_abnormalStates;
	}

	//状態異常を返す(ID)
	int GetAbnormalStateID(int num);
	

	//使うpythonのファイルを設定する
	//st: ファイルの名前
	void SetpyFile(std::string* st)
	{
		m_pyFile = st;
	}

	//使うpythonファイルの名前を返す
	std::string* GetpyFile()
	{
		return m_pyFile;
	}

	//使うvisualScriptのファイルを設定する
	//st: ファイルの名前
	void SetVisualScriptAI(std::string* st)
	{
		m_pyFile = st;
		m_visualAI = new VisualScriptAI(this, st);
		m_isUseVSAI = true;
	}

	//HPを返す
	float GetHP()
	{
		return m_HP;
	}

	void SetHP(float hp)
	{
		if ((m_maxHP - hp) < 0)
		{
			m_HP = m_maxHP;
		}
		else 
			m_HP = hp;
	}

	//ダメージ
	//d: 食らうダメージ
	void Damage(float d)
	{
		//m_HP -= d;
		m_Damage += d;
	}

	void DamageEx(float d)
	{
		m_DamageEx += d;
	}

	//MPを返す
	float GetMP()
	{
		return m_MP;
	}

	void SetMP(float mp)
	{
		if ((m_maxMP - mp) < 0)
			m_MP = m_maxMP;
		else 
			m_MP = mp;
	}

	void SetMPrecv(float rmp)
	{
		m_MPrecov = rmp;
	}

	float GetMPrecv()
	{
		return m_MPrecov;
	}

	float GetMaxHP()
	{
		return m_maxHP;
	}
	float GetMaxMP()
	{
		return m_maxMP;
	}
	void SetMaxHP(float max)
	{
		m_maxHP = max;
	}
	void SetMaxMP(float max)
	{
		m_maxMP = max;
	}

	float GetDefense()
	{
		return m_Defense;
	}

	float GetExDefense()
	{
		return m_ExDefense;
	}

	void SetDefense(float d)
	{
		m_Defense = d;
	}

	void SetExDefense(float d)
	{
		m_ExDefense = d;
	}


	float GetAttack()
	{
		return m_Attack;
	}

	float GetExAttack()
	{
		return m_ExAttack;
	}

	float GetSpeed()
	{
		return m_speed;
	}

	//コライダーの半径を返す
	float Getradius()
	{
		return m_radius;
	}

	//コライダーの高さを返す
	float Getheight()
	{
		return m_height;
	}

	//現在のポジションを返す
	CVector3 Getpos()
	{
		return m_pos;
	}

	//ポジションを設定する
	//v: 設定するポジション
	void Setpos(CVector3 v);

	float GetPspeed()
	{
		return m_speed;
	}

	//スピードを返す
	CVector3 Getspeed()
	{
		return m_movespeed;
	}

	//スピードを設定する
	//v: スピードベクトル
	void Setspeed(CVector3 v)
	{
		m_oldmovespeed = m_movespeed;
		m_movespeed = v;
	}

	void SetSpeed(float speed) {
		m_speed = speed;
	}

	void SetDefensePower(float pow) {
		m_Defense = pow;
	}

	void SetExDefensePower(float pow) {
		m_ExDefense = pow;
	}

	void SetAttackPower(float pow) {
		 m_Attack = pow;
	}

	void SetExAttackPower(float pow) {
		m_ExAttack = pow;
	}

	//
	CVector3 GetFrontvec()
	{
		CVector3 vec = m_movespeed;
		if (vec.Length() > 1.0f)
		{
			vec.Normalize();
			m_front = vec;
		}

		return m_front;
	}

	CQuaternion GetRotation()
	{
		return m_rot;
	}
	void SetRotation(CQuaternion rot);

	//今歩いているかを設定する
	void Setiswalk(bool b)
	{
		m_iswalk = b;
	}

	//チームを返す
	int Getteam()
	{
		return m_team;
	}

	//チームを設定する
	//t: チーム
	void Setteam(int t)
	{
		m_team = t;
	}

	//numを返す
	int Getnum()
	{
		return m_num;
	}

	//numを設定する
	//num: num
	void Setnum(int num)
	{
		m_num = num;
	}

	//IDを返す
	int GetID()
	{
		return m_ID;
	}

	//技のスタックをクリアする
	void ClearActionStack() {
		m_actions.clear();
	}

	//これいらない
	Monster* Getmon()
	{
		return this;
	}

	//アクションを加えるときに使う
	//ma: モンスターアクション
	void AddAction(MonsterAction* ma);

	//行っている・行う予定のアクションを返す
	std::vector<MonsterAction*> Getactions()
	{
		return m_actions;
	}

	void ReleaseMAL();
	void ReleaseMark();

	//アニメーションさせるときは必ずこいつらを使うこと。
	void anim_idle();
	void anim_walk();
	void anim_atack();
	void anim_defenseF();
	void anim_defenseM();
	void anim_defenseE();
	void anim_extra1();

	bool isAnimPlay();

	//アニメーションの状態
	enum anim
	{
		en_idle,
		en_walk,
		en_atack,
		en_defenseF,
		en_defenseM,
		en_defenseE,
		en_extra1,
		en_extra2,
		en_extra3,
		en_extra4,
		en_extra5,
	};

	void end()
	{
		m_end = true;
	}

protected:
	//const char* m_pyFile = NULL;				//使うpythonファイルの名前
	std::string* m_pyFile = nullptr;
	int m_ID = 0;								//モンスターの種類を判断するためのID
	int m_num = 0;								//背番号みたいな感じ
	int m_team = 0;								//チーム番号

	CharacterController m_cc;					//キャラコン
	float m_radius = 0.0f;						//半径
	float m_height = 0.0f;						//高さ
	SkinModelRender* m_smr = nullptr;			//スキンモデルレンダー
	float m_HP = 0;								//HP
	float m_maxHP = 0;
	float m_MP = 0;								//MP
	float m_maxMP = 0;
	float m_Defense = 0;						//防御力
	float m_ExDefense = 0;						//特殊防御力
	float m_Attack = 0;							//攻撃力
	float m_ExAttack = 0;						//特殊攻撃力

	float m_Damage = 0;							//ダメージ
	float m_DamageEx = 0;						//特殊ダメージ

	float m_MPrecov = 3;

	float m_speed = 0.0f;						//スピード
	float m_gravity = 50.0f;					//重力
	
	CVector3 m_movespeed = CVector3::Zero();	//ムーブスピード
	CVector3 m_oldmovespeed = CVector3::Zero();	//古のムーブスピード
	CVector3 m_front = CVector3::Zero();		//前方向
	bool m_iswalk = false;						//
	bool m_isKnockback = false;					//
	CVector3 m_vKnockback = CVector3::Zero();	//
	CVector3 m_vSubKnock = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();			//ポジション
	CQuaternion m_rot = CQuaternion::Identity();//回転
	int m_turncount = 0;
	float m_rotangle = 0;

	AbnormalState m_abnormalState = abNull;
	//std::vector<AbnormalState> m_abnormalStates;
	std::vector<ACTEffectGrant*> m_abnormalStates;

	PythonBridge* m_PB;

	ActionID* m_UseAction;
	int m_useActionSize = 0;
	std::vector<MonsterAction*> m_actions;		//使うアクション
	en_State m_state = en_NowLoading;
	bool isLoading = false;

	MonsterActionList* m_MAL = nullptr;
	bool m_dmal = false;

	MonsterMarker* m_marker = nullptr;

	MonsterEffect* m_effect;

	int m_AnimNum = 0;							//アニメーションの個数

	float m_actionTime = 0.0f;
	float m_MPRecvTime = 0.0f;

	bool m_end = false;

	bool m_isUseVSAI = false;					//visualAIを使うかどうか
	VisualScriptAI* m_visualAI = nullptr;		//visualAIのいんすたんす

	float m_limitDist = 1036.f;
};