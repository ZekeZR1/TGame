#pragma once

class GameCamera;
//以前保存したAIエディットを開くためのGUI
class AIEditNodeMenuOpen :public GameObject
{
public:
	//デストラクタ
	void OnDestroy();
	//コンストラクタ
	void Awake() override;

	//スタート
	bool Start();
	//アップデート
	void Update();

private:
	SpriteRender* m_back = nullptr;			//後ろのやつ
	std::vector<SpriteRender*> m_buttons;	//ボタン
	std::vector<FontRender*> m_fonts;		//ボタンのフォント


};