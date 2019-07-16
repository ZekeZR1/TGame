#pragma once

class GameCursor;

//GOがクリックされたかを返すだけのクラス
class GObutton :public GameObject
{
public:
	//初期化
	GObutton();

	/*
	初期化関数
	arg:
		cursor カーソルのポインタ
		pos ボタンのポジション
	*/
	void init(GameCursor* cursor,CVector3 pos);

	//デストラクタ
	void OnDestroy();

	//更新
	void Update();

	//更新
	void UpdateEx();

	//クリックされました？
	bool isClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_button = nullptr;	//botan no supuraito
	bool m_isOver = false;				//マウスオーバーされてる？
	bool m_isClick = false;				//クリックされたの？

	GameCursor* m_cursor = nullptr;		//ka-so-
};