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

private:
	int button = 1;
	bool menu = false;
	std::vector<FontRender*> m_fonts;
	CVector3 m_position = CVector3::Zero();
	GameCursor* m_gamecursor;
	SpriteRender * m_spriteRender;
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