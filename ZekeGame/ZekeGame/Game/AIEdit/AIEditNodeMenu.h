#pragma once
class GameCursor;
class ShowMonsters;
class AIEditNodeProcess;
class AIEditNodeButton;
class AIEditLine;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeClick;
class AIEditNodeMass;
class AIEditNodeNum;
class AIEditNodeOrder;
class AIEditNodeTarget;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class ModeSelect;
class AIEditNodeMenuConfirmation;
class AIEditNodeMenuWindow;
class AIEditNodeSelectFonts;
class AIEditNodeSelectButtons;
class AIEditNodeDeleteKey;
class AIEditNodeMenu : public GameObject
{

public:
	~AIEditNodeMenu();


	bool Start();
	void Update();
	void BackMenu();
	void Menuwin();

	void SetWindowActive(bool activeFlag) {
		m_isActive = activeFlag;
	}

	void SetMenuconf(bool a)
	{
		menuconf = a;
	}

	void SetMenu(bool a)
	{
		menu = a;
	}

	bool GetMenu()
	{
		return menu;
	}

private:
	int button = 3;          //メニューの選択ボタンの数。
	bool menu = false;
	bool menuconf = false;
	bool isActive = true;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();

	std::vector<SpriteRender*> m_buttons;
	std::vector<SpriteRender*> m_spriteRender2;
	std::vector<FontRender*> m_fonts;
	std::vector<SpriteRender*> sp;

	SpriteRender* m_spriteRender = nullptr;

	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditLine* m_aieditline = nullptr;
	AIEditNode* m_aieditnode = nullptr;
	AIEditNodeInequ* m_aieditnodeinequ = nullptr;
	AIEditNodeClick* m_aieditnodeclick = nullptr;
	AIEditNodeMass* m_aieditnodemass = nullptr;
	AIEditNodeNum* m_aieditnodenum = nullptr;
	AIEditNodeOrder*m_aieditnodeorder = nullptr;
	AIEditNodeTarget* m_aieditnodetarget = nullptr;
	AIEditNodeTechnique* m_aieditnodetechnique = nullptr;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate = nullptr;
	AIEditNodeMenuConfirmation* m_aieditnodemenuconfirmation = nullptr;
	AIEditNodeMenuWindow* m_aieditnodemenuwindow = nullptr;
	ModeSelect* m_modeselect = nullptr;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts = nullptr;
	AIEditNodeSelectButtons* m_aieditnodeselectbuttons = nullptr;
	AIEditNodeDeleteKey* m_aieditnodedeletekey = nullptr;
	ShowMonsters* m_monstersInfo = nullptr;
	GameCursor* m_gamecursor = nullptr;
};