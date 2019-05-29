#pragma once


struct chank;
class SuperMonsterSelect;
typedef SuperMonsterSelect SMS;
class GameCursor;

class MonAIPresets;
struct Person
{
	int aimode = 0;
	int monID = 0;
	int stlen = 0;
	char str[255];
	int stind = 0;
};
struct Preset
{
	~Preset()
	{
		for (int i = 0; i < 3; i++)
			delete person[i];
	}
	Person* person[3];
};

class MonAIPresetOpenSuper :public GameObject
{
public:
	//デストラクタ
	~MonAIPresetOpenSuper();

	//Start
	bool Start();

	//initialize function
	//args:
	//	sms:シーンのインスタンス
	//	cursor:カーソル
	//	team:チーム
	//	tx:fontRenderに表示する文字
	void init(SMS* sms, GameCursor* cursor, const wchar_t* tx,CVector3 pos, int team = 0);

	//Update
	void Update();

	//UpdateしないUpdate
	void UpdateEx();

	//開く。ぜっていにiconがひらく。
	void Open();

	//閉じる。
	void Close();

	//クリックされたンゴwwww
	bool IsClick()
	{
		return m_isClick;
	}

	//開いていますか？
	bool IsOpen()
	{
		return m_isOpen;
	}

	//get プリセット
	Preset** GetPresets()
	{
		return m_presets;
	}

	//仮想関数
	//これを継承させたやつが使う。
	//プリセットのグラフィックが開かれて、いづれかのプリセットがクリックされたときに反応しちゃうやつ。意外と敏感なのね。
	virtual void Execute(int num) {};

	//presetデータが歩かないか。なかった場合はそのままinitPresetにＧＯ！
	FILE* FindPreset();
	//presetデータがない時用のpreset初期化
	FILE* initPreset();

protected:
	SpriteRender* m_back = nullptr;		//後ろに表示する半透明のやつ。
	SpriteRender* m_button = nullptr;	//ボタンのスプライト
	SpriteRender* m_dummy = nullptr;	//だみー
	static MonAIPresets* m_maps;		//Iconsの塊

	FontRender* m_font = nullptr;		//フォントレンダー

	static Preset* m_presets[6];				//プリセット
	static std::map<int, int> m_aimap;		//ai用のmap

	SMS* m_sms = nullptr;				//シーンのインスタンス
	GameCursor* m_cursor = nullptr;		//カーソル
	int m_team = 0;						//適応されるチーム


	enum Type
	{
		enLoader,
		enSaver,
	};
	Type m_type = enSaver;				//継承したやつが何をするやつなのか。

	static bool m_isAllNone;			//プリセットが何も入っていないときtrue

	bool m_isSelect = false;			//マウスオーバーさんのフラグ

	bool m_isClick = false;				//クリックフラグ
	bool m_isOpen = false;				//オペンフラグ

	bool m_first = true;				//初めてなの。

	SpriteRender* m_close = nullptr;	//とじるボタン
	FontRender* m_fclose = nullptr;		//とじるフォンと

	static bool m_isInit;				//初期化された？
};

