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
	void FontsConfirmation();

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
	bool contact1 = false;
	bool contact2 = false;

	float scale = 0.8;

	CVector2 SetShadowPos = { 0.5f,-0.5f };

	CVector3 m_position = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender* m_spriteRender = nullptr;

	GameCursor* m_gamecursor = nullptr;
	AIEditNodeButton* m_aieditnodebutton = nullptr;
	AIEditNodeOrder* m_aieditnodeorder = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;

};