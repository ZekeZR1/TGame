#pragma once

#include "../Title/SuperMonsterSelect.h"
class ToAiEditModeButton;
class GameCursor;
class RatingInfo;
class MonAIPresetOpenSuper;
class Fade;
class ReturnButton;
class GObutton;
class MonsterSelectBack;
class NetAISelect :public SuperMonsterSelect
{
public:
	void OnDestroy() override;
	bool Start();
	void Update();

	std::vector<std::string> GetFiles()
	{
		return m_files;
	}
	std::vector<PMMonster*> GetPMMonster()
	{
		return m_pmms;
	}
private:
	CFont font;
	std::vector<std::string> m_files;
	int monai[6] = { 0 };
	int curpos = 0;
	bool sel = false;

	GameCursor* m_cursor = nullptr;

	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	//std::vector<SpriteRender*> m_monicon;

	//SpriteRender* m_GO = nullptr;
	SpriteRender* m_back = nullptr;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_returnMoji = nullptr;

	//rating information
	SpriteRender* m_info = nullptr;
	CVector3 m_infoPos = { 550.f,-200.f ,0.f };

	bool isReturnOver = false;
	CVector2 m_returnS = { 604,256 };

	Sound* m_BGM = nullptr;
	float m_vol = 1;

	//MonAIPresetOpen* m_mapo = nullptr;
	MonAIPresetOpenSuper* m_msRed = nullptr;		//presetのセーブ用
	MonAIPresetOpenSuper* m_mlRed = nullptr;		//presetのロード用

	Fade* m_fade = nullptr;			//フェード
	bool m_isfade = false;
	bool m_isBackFade = false;
	RatingInfo* m_status = nullptr;

	ReturnButton* m_returnButton = nullptr;			//戻るボタン

	GObutton* m_GOb = nullptr;						//GO botan
	ToAiEditModeButton* m_aiButton = nullptr;
	MonsterSelectBack* m_msback = nullptr;			//はいけい
};