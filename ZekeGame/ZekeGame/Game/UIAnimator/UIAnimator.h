#pragma once

struct sUI
{
	wchar_t name[256] = { 0 };
	CVector2 dimensions = { 0,0 };
	CVector3 pos = CVector3::Zero();
	CVector3 scale = CVector3::Zero();
	CQuaternion rot = CQuaternion::Identity();
};

struct UIkeyFrame
{
	int num = 0;
	CVector3 pos = {0,0,0};
	CVector3 scale = { 0,0,0 };
	CQuaternion rot = { 0,0,0,1 };
};

//UIのアニメーション
struct UIAnim
{
	std::vector<UIkeyFrame> frames;
};

class UIAnimator :public GameObject
{
public:
	void OnDestroy();
	/*
	UIをロードする
	args:
		path: path
		fanc:	ラムダ式
	*/
	void loadUI(const wchar_t* path,std::function<SpriteRender*(sUI* ui,bool &isfook)> func);
	/*
	アニメーションを再生
	path: path
	*/
	void playAnim(const wchar_t* path);

	//Update
	void Update();

	// 今、アニメーションしてますか？
	bool isAnimation()
	{
		return m_isAnimation;
	}

	//再生のスピードを設定する
	//初期は30
	void setSpeed(float sp)
	{
		m_speed = sp;
	}

	//ループするの？
	bool isLoop()
	{
		return m_isLoop;
	}

	//ループしますか、しませんか？
	void setLoopFlag(bool b)
	{
		m_isLoop = b;
	}

	//pojisyon を設定する
	void setPos(CVector3 pos)
	{
		m_pos = pos;
	}

	//ポジションを返す
	CVector3 getPos()
	{
		return m_pos;
	}
private:
	std::vector<SpriteRender*> m_Sprits;		//loadUIで取得したspriterenderたち

	std::vector<UIAnim*> m_anims;				//現在実行しているアニメーション
	int m_frameCount = 0;								//フレーム数
	float m_time = 0;										//時間
	float m_frame = 0;										//現在のフレーム
	float m_speed = 30.f;							//speed
	bool m_isAnimation = false;					//アニメーションしてる？
	bool m_isLoop = false;					//ループスループ？

	CVector3 m_pos = CVector3::Zero();		//ポジション
};

