#pragma once

class GameCursor;
class AIEditNodeButton;
class AIEditNodeOrder;
class AIEditNodeProcess;
class AIEditNodeAbnormalState : public GameObject
{

public:
	~AIEditNodeAbnormalState();

	bool Start();
	void Update();
	void Order();

	enum Abnormal {

		endoku =600,
		enyakedo,
		enhyouketu,
		ensutan,
		ennull = 0,
	};

	int GetAbnormal()
	{
		return m_abnormal;
	}

	bool Getabnormalfont()
	{
		return abnormalfont;
	}

private:

	Abnormal m_abnormal = ennull;
	int button = 4;
	bool Choice6 = false;
	bool abnormalfont = false;

	std::vector<FontRender*> m_fonts;
	GameCursor* m_gamecursor;
	SpriteRender* m_spriteRender;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeOrder* m_aieditnodeorder;
	AIEditNodeProcess* m_aieditnodeprocess;

	CVector3 m_position = CVector3::Zero();

	std::vector<AIEditNodeButton*> m_nodebuttons;
	

};