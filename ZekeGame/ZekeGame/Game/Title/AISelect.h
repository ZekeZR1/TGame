#pragma once

class SuperMonsterSelect;
class PvPModeSelect;
class AIMSelect;
class GameCursor;
class PMMonster;
class IconAI;
class AISelect :public GameObject
{
public:
	~AISelect();
	bool Start();
	void init(PMMonster* pmm,AIMSelect* aims);
	void Update();
	void PostRender();

	//pythonでつくったAIの一覧を表示する
	void CreatePyAI();
	
	//VisualScriptで作ったAIの一覧を表示する
	void CreateViAI();

	//AIの一覧をけす
	void DeleteAI();
private:
	PMMonster* m_pmm;
	AIMSelect* m_AIMS;
	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;

	float m_minScroll = 0.0f;
	float m_maxScroll = 0.0f;
	float m_scroll = 316.5f;

	std::vector<IconAI*> m_icons;
	SuperMonsterSelect* m_ppms = nullptr;

	SpriteRender* m_AIsel = nullptr;

	FontRender* m_title = nullptr;			//上に表示する文字


	enum AIMode
	{
		enPy,
		enVi,
	};
	int m_AImode = enPy;

	SpriteRender* m_changeAI = nullptr;		//visualAIとpythonAIとの切り替え用のsprite
	FontRender* m_CAfont = nullptr;			//visualAIとpythonAIとの切り替え用のフォント
};