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
class AIEditNodeMenu : public GameObject
{

public:
	~AIEditNodeMenu();


	bool Start();
	void Update();
	void BackMenu();
	void Menuwin();

private:
	int button = 2;
	bool menu = false;
	std::vector<FontRender*> m_fonts;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	CVector3 m_position2 = CVector3::Zero();
	CVector3 m_position3 = CVector3::Zero();
	CVector3 m_position4 = CVector3::Zero();
	CVector3 m_position5 = CVector3::Zero();

	GameCursor* m_gamecursor;

	SpriteRender* m_spriteRender;
	std::vector<SpriteRender*> m_buttons;
	std::vector<SpriteRender*> m_spriteRender2;
	SpriteRender* m_spriterender2;
	SpriteRender* m_spriterender3;
	SpriteRender* m_spriterender4;
	SpriteRender* m_spriterender5;

	AIEditNodeButton* m_aieditnodebutton;
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
	ModeSelect* m_modeselect;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};