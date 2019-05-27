#pragma once
#include "SuperMonsterSelect.h"
class PMMonster;
class GameCursor;
class SuperMonsterSelect;
class Fade;

class ReturnButton;

class MonAIPresetOpen;
class MonAIPresetOpenSuper;
class PvPModeSelect :public SuperMonsterSelect
{
public:
	~PvPModeSelect();
	void OnDestroy();
	bool Start() override;
	void Update() override;
	void PostRender() override;
	void LoadFiles();
	
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
	int monai[6] = {0};
	int curpos = 0;
	bool sel = false;

	GameCursor* m_cursor;

	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	//std::vector<SpriteRender*> m_monicon;

	SpriteRender* m_GO = nullptr;
	SpriteRender* m_back = nullptr;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_returnMoji = nullptr;
	bool isReturnOver = false;
	CVector2 m_returnS = { 604,256 };

	ReturnButton* m_returnButton = nullptr;

	Sound* m_BGM = nullptr;
	float m_vol = 1;

	//MonAIPresetOpen* m_mapo = nullptr;
	MonAIPresetOpenSuper* m_msRed = nullptr;		//presetのセーブ用
	MonAIPresetOpenSuper* m_mlRed = nullptr;		//presetのロード用(紅組用の)
	MonAIPresetOpenSuper* m_msBlue = nullptr;		//presetのセーブ用
	MonAIPresetOpenSuper* m_mlBlue = nullptr;		//presetのロード用(青組用の)

	Fade* m_fade = nullptr;
	bool m_isfade = false;
};