#pragma once

struct Preset;
class MonAIPresetIcon;

class GameCursor;
class MonAIPresetIcons :public GameObject
{
public:
	void OnDestroy() override;
	//デストラクタ
	~MonAIPresetIcons();

	//Start
	bool Start();

	//初期化関数
	//args:
	//	monids: モンスターのIDの配列
	//	pypath: pythonのパスの配列
	//	pos:	ポジション
	void init(Preset* preset,CVector3 pos,GameCursor* cur);

	void UpdateIcon();

	//Update
	void Update();

	void Setpos(CVector3 pos);
	void Setrot(float rot);

	//クリックしたのか…？俺以外のやつと…？
	bool IsClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_back = nullptr;				//後ろのやつ
	SpriteRender* m_dummy = nullptr;			//後ろのやつのダミー
	MonAIPresetIcon* m_mapi[3] = { nullptr };	//icon群
	FontRender* m_Nonefont = nullptr;				//プリセットに何も保存されていないときに使うやつ
	CVector3 m_fontpos = { 0,0,0 };
	bool m_isNone = 0;
	CVector3 m_pos = { 0,0,0 };

	GameCursor* m_cursor = nullptr;				//かーそー

	bool m_isClick = false;						//クリックされたのかどうか。

	bool m_isSelect = false;					//マウスオーバーのフラッグＹＯ！。

	Preset* m_preset;							//purisetto
};