#pragma once

class AIEditNode;
class AIEditNodeOrder;
class AIEditNodeTarget;
class AIEditNodeProcess;
class AIEditNodeSelectFonts;
class AIEditLine : public GameObject
{

public:

	~AIEditLine();

	bool Start() override final;
	void Update() override final;
	void makeLine();
	void OnDestroy();

	CVector3 GetPos()
	{

		return m_pos;
	}

	CVector3 SetPos(CVector3 a)
	{

		m_pos = a;
		return m_pos;
	}

private:

	float x = 50;

	bool Choice1 = false;
	bool m_ismakeLine = false;

	CVector3 m_pos = CVector3::Zero();

	SpriteRender * m_spriteRender = nullptr;
	FontRender* m_font = nullptr;

	AIEditNodeOrder * m_aieditnodeorder = nullptr;
	AIEditNode * m_aieditnode = nullptr;
	AIEditNodeTarget* m_aieditnodetarget = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts = nullptr;


};