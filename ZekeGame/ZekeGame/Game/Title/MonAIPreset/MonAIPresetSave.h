#pragma once

class GameCursor;
class SuperMonsterSelect;
struct chank
{
	int monID = 0;
	int stlen = 0;
	char str[255];

};
class MonAIPresetSave :public GameObject
{
public:
	void OnDestroy() override;
	bool Start();

	//初期化関数
	//arg:
	//	ppms: シーンのインスタンス
	//	No: 何番目のプリセットか
	//	cursor: カーソル
	void init(SuperMonsterSelect* ppms,int No,GameCursor* cursor);

	void Update();

	//セットポｓ
	//pos: セットするポジション
	void setPos(CVector3 pos)
	{
		m_pos = pos;
	}
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;

	GameCursor* m_cursor = nullptr;

	int num = 0;
	SuperMonsterSelect* m_ppms = nullptr;

	CVector3 m_pos = CVector3::Zero();
};