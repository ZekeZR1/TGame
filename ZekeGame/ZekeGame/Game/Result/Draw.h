#pragma once

class UIAnimator;
//バトルで両方のチームが全滅してしまった時の処理
class BattleDraw :public GameObject
{
public:
	//初期化
	BattleDraw();
	//Start
	bool Start();
	//更新
	void Update();
private:
	SpriteRender* m_drawSp = nullptr;	//DRAW MOJI
};