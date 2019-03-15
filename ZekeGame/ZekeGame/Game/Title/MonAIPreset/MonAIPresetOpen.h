#pragma once

class SuperMonsterSelect;
class GameCursor;
class MonAIPresetOpen :public GameObject
{
public:
	void OnDestroy();
	//Start
	bool Start();

	//初期化関数NewGOしたらすぐに使う
	//arg:
	//	sms: SuperMonsterSelectを継承したモンスター選択画面のインスタンス
	//	cursor: 今のシーンで使用されているカーソルのインスタンス。
	//	team: どっちのチームにプリセットを適応するか。
	//			ダンジョンの場合は入力しなくてもいい。
	void init(SuperMonsterSelect* sms,GameCursor* cursor,int team = 0);

	//Update
	void Update();

	//MonAIPresetを開く.
	void OpenPreset();

	//クリックされたか。
	bool IsClick()
	{
		
		return m_isClick;
	}

	//今プリセットの画面が開いているか。
	bool IsOpen()
	{
		return m_isOpen;
	}

	//閉じる
	void Close()
	{
		m_isOpen = false;
	}

private:
	SpriteRender* m_button = nullptr;		//ボタンのスプライト
	SpriteRender* m_dummy = nullptr;		//ダミースプライト
	FontRender* m_font = nullptr;			//フォント

	SuperMonsterSelect* m_sms =nullptr;		//シーン
	GameCursor* m_cursor = nullptr;			//カーソル
	int m_team = 0;							//チーム
	bool m_isClick = false;					//クリックされたか。
	bool m_isOpen = false;					//今開いているか。
};