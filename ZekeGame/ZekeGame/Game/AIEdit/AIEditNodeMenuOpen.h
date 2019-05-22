#pragma once


#include "AIEditNodeOrder.h"

struct sOrderLine
{
	~sOrderLine()
	{
		if (one != nullptr) delete one;
		if (two != nullptr) delete two;
		if (three != nullptr) delete three;
	}
	sOrder* one = nullptr;
	sOrder* two = nullptr;
	sOrder* three = nullptr;
};

class GameCursor;
class AIEditNodeSelectButtons;
//以前保存したAIエディットを開くためのGUI
class AIEditNodeMenuOpen :public GameObject
{
public:
	//デストラクタ
	void OnDestroy();
	//コンストラクタ
	void Awake() override;

	//初期化
	//arg:
	//	nsb:戻ると起用のやつ
	//	cursor:カーソル
	void init(AIEditNodeSelectButtons* nsb,GameCursor* cursor)
	{
		m_nsb = nsb;
		m_cursor = cursor;
	}

	//スタート
	bool Start();
	//アップデート
	void Update();

	void OpenAI(const char* path);

private:
	SpriteRender* m_back = nullptr;			//後ろのやつ
	std::vector<SpriteRender*> m_buttons;	//ボタン
	std::vector<FontRender*> m_fonts;		//ボタンのフォント

	SpriteRender* m_close = nullptr;		//閉じるボタン
	FontRender* m_cfont = nullptr;			//閉じるのフォント

	FontRender* m_head = nullptr;			//見出し

	AIEditNodeSelectButtons* m_nsb = nullptr;//メニュー軍

	GameCursor* m_cursor = nullptr;			//かーそー

	sOrderLine m_orders[8];					//orderたち

	std::vector<SpriteRender*> m_marks;		//mark
};