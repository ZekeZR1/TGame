#pragma once

class SuperMonsterSelect;
class GameCursor;
class MonAIPresetOpen;
class MonAIPresetSave;
class MonAIPresetLoad;
class MonAIPreset :public GameObject
{
public:
	~MonAIPreset();
	void OnDestroy();
	bool Start();

	//初期化関数
	//arg:
	//	sms: しーんのインスタンス
	//	cursor:今のシーで使われているインスタンス
	//	mapo:これを開くために使ったインスタンス
	//	team:チーム。
	void init(SuperMonsterSelect* sms, GameCursor* cursor, MonAIPresetOpen* mapo,int team);
	void Update();

	void Close();

private:
	FontRender* m_fonts[6] = {nullptr};		//6個詰めフォント
	SpriteRender* m_prsp[6] = { nullptr };	//6個詰めスプライト

	MonAIPresetSave* m_maps[6] = { nullptr };	//プリセットのセーブするやつ6個詰め
	MonAIPresetLoad* m_mapl[6] = { nullptr };	//プリセットのロードするやつ6個詰め

	SuperMonsterSelect* m_sms = nullptr;
	GameCursor* m_cursor = nullptr;
	MonAIPresetOpen* m_mapo = nullptr;
	int m_team = 0;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_rDummy = nullptr;
};