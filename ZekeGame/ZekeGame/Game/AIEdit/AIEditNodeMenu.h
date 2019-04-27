#pragma once
class GameCursor;
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

	std::vector<FontRender*> m_fonts;
	std::vector<SpriteRender*> sp;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();

	GameCursor* m_gamecursor;

	SpriteRender* m_spriteRender = nullptr;
	std::vector<SpriteRender*> m_buttons;
	std::vector<SpriteRender*> m_spriteRender2;

	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditLine* m_aieditline;
	AIEditNode* m_aieditnode;
	AIEditNodeInequ* m_aieditnodeinequ;
	AIEditNodeClick* m_aieditnodeclick;
	AIEditNodeMass* m_aieditnodemass;
	AIEditNodeNum* m_aieditnodenum;
	AIEditNodeOrder*m_aieditnodeorder;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate;
	AIEditNodeMenuConfirmation* m_aieditnodemenuconfirmation;
	AIEditNodeMenuWindow* m_aieditnodemenuwindow;
	ModeSelect* m_modeselect;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts;
	AIEditNodeSelectButtons* m_aieditnodeselectbuttons;
	AIEditNodeDeleteKey* m_aieditnodedeletekey;

};