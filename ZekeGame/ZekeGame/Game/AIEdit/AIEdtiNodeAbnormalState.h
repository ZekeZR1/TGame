#pragma once

class GameCursor;
class AIEditNodeButton;
class AIEditNodeOrder;
class AIEditNodeAbnormalState : public GameObject
{

public:
	~AIEditNodeAbnormalState();

	bool Start();
	void Update();
	void Order();

	enum Abnormal {

		endoku,
		enyakedo,
		enhyouketu,
		ensutan,
		ennull,
	};

	int GetAbnormal()
	{
		return m_abnormal;
	}

private:

	Abnormal m_abnormal = ennull;
	int button = 4;
	bool Choice6 = false;
	std::vector<FontRender*> m_fonts;
	GameCursor* m_gamecursor;
	SpriteRender* m_spriteRender;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeOrder* m_aieditnodeorder;

	CVector3 m_position = CVector3::Zero();

	std::vector<AIEditNodeButton*> m_nodebuttons;
	

};