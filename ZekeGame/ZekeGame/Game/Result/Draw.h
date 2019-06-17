#pragma once

class UIAnimator;
class Fade;
//バトルで両方のチームが全滅してしまった時の処理
class BattleDraw :public GameObject
{
public:
	//初期化
	BattleDraw();

	//デストラクタ
	void OnDestroy();

	//Start
	bool Start();
	//更新
	void Update();

	/*
	モードをセットする
	*/
	void SetPVPMode(int n)
	{
		m_monsel = n;
	}

	/*
	ダンジョンの番号をセットする
	*/
	void SetDunNum(int n)
	{
		m_dunNum = n;
	}

	//UIアニメーションを再生
	void playDraw();
private:
	SpriteRender* m_drawSp = nullptr;	//DRAW MOJI
	UIAnimator* m_uia = nullptr;		//UIAnimator

	FontRender* m_fr = nullptr;			//クリックしてください

	Fade* m_fade = nullptr;				//フェード

	bool isEND = false;					//終わった・・・

	int m_monsel = 0;					//どのモードか
	int m_dunNum = 0;					//ダンジョンの番号
};