#pragma once

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

	//void SetPosy(bool a) {

	//	y = a;
	//}

	void SetPro(bool a)
	{

		process = a;
	}

private:

	bool Choice0 = false;
	bool process = false;

    int x = -446;
	int y = 288;

	//int y = 0;
	

	GameCursor * m_gamecursor;
	SpriteRender * m_spriteRender;
	CVector3 m_position = CVector3::Zero();
	AIEditNode* m_aieditnode;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeProcess* m_aieditnodeprocess;
};