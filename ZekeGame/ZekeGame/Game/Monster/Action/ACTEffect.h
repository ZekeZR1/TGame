#pragma once

class Monster;

class ACTEffectGrant :public GameObject
{
public:
	/*
	デストラクタ
	*/
	~ACTEffectGrant();

	/*
	初期化
	インスタンスを生成した時には必ずこれを使う。
	arg:
		effect:ここで使うエフェクト
		target:引っ付いていくモンスター
		state:このクラスで何をするか、
		dam:食らわすダメージ
		time:ダメージのスパン。0未満の場合は毎フレーム
	*/
	void init(CEffect* effect, Monster* target, int state = enNull, float dam = 0,float time = -1,float endTime = 0);

	/*
	Update
	*/
	void Update();

	//状態異常の設定
	void SetAbnormalState(int abn);
	//状態異常を返す。
	int GetAbnormalState()
	{
		return m_abnormal;
	}

	//これを設定するとダメージを食らわせたりできる。
	enum State
	{
		enNull,		//何もしない
		enDamage,	//ダメージ
		enCC,	//移動妨害
		enbuffAtc,
	};

private:
	State m_state = enNull;

	int m_abnormal = 0;

	float m_damTime = 0;
	float m_dam = 0;

	float m_efTime = 0;
	float m_time = 0;
	float m_endTime = 0;
	CEffect* m_effect = nullptr;
	Monster* m_target = nullptr;
};