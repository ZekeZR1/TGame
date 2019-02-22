#pragma once
class AIEditMode;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeClick;
class AIEditLine;
class GameCursor;
class AIEditNodeTarget;
class AIEditNodeProcess;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	
	bool Start() override final;
	void Update() override final;
	void DeleteGOs();
	void Fonts();

	bool GetTec()
	{

		return Technique;
	}

	void SetTec(bool a)
	{
		Technique = a;
	}

	CVector3 GetPos()
	{

		return m_pos;
	}


private:


	bool Technique = false;		//ãZÇëIëÇµÇΩÇ∆Ç´trueÇ…Ç»ÇÈÅBÅ@
	int num = 1;

	std::vector<FontRender*> m_fonts;
	CVector3 m_pos = CVector3::Zero();
	GameCursor * m_gamecursor;
	AIEditMode * m_aieditmode;
	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeClick* m_aieditnodeclick;
	AIEditLine * m_aieditline;
	SpriteRender * m_spriteRender;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate;

};