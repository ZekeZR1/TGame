#pragma once


class AIEditNodeButton : public GameObject
{

public:
	~AIEditNodeButton();
	bool Start();
	void Update();
	void Awake();
	
	//ボタンの数を指定。
	void SetButton(int num)
	{
		button = num;
	}

	//座標を指定。
	void SetPos(CVector3 pos)
	{
		kari = pos;
	}

	//プライオリティを設定。
	void SetPri(int pri)
	{
		priority = pri;
	}

	SpriteRender * GetSpriteRender()
	{
		return m_spriteRender;
	}

	CVector3 GetPos() {
		return kari;
	}

private:

	int sizex = 140;      //ボタンのサイズx
	int sizey = 50;       //ボタンのサイズy
	int button = 0;       //ボタンの数だよ。   
	int priority = 0;     //描画優先順位
	int x = 0;   
	int y = 140;

	CVector3 kari = CVector3::Zero();

	SpriteRender * m_spriteRender = nullptr;

	GameCursor * m_gamecursor = nullptr;

};