#pragma once
class AIEditNodeSelectButtons;
class GameCursor;
class AIEditNode;
class AIEditNodeTarget;
class AIEditNodeProcess;
class AIEditNodeClick : public GameObject
{
public:

	~AIEditNodeClick();

	bool Start() override final;
	void Update() override final;
	void SetPosition(CVector3 m_pos);

	void GetChoice0(bool a)
	{
		Choice0 = a;
	}

	CVector3 GetPosition()
	{
		return m_position;
	}

	void SetPro(bool a)
	{
		process = a;
	}

private:

	bool Choice0 = false;
	bool process = false;	
	bool m_isFsc = true;						//font no scale
	bool m_isOver = false;						//mouseover?

	float m_fontS = 1.f;						//font Scale

	CVector3 m_position = CVector3::Zero();

	SpriteRender* m_spriteRender = nullptr;
	SpriteRender* m_button = nullptr;			//botan
	FontRender* m_font = nullptr;				//click MOJI

	GameCursor * m_gamecursor = nullptr;
	AIEditNode* m_aieditnode = nullptr; 
	AIEditNodeTarget* m_aieditnodetarget = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectButtons* m_aieditnodeselectbuttons = nullptr;


};