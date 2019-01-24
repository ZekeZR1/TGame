#pragma once
class AIEditMode;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeClick;
class GameCursor;
class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	
	bool Start() override final;
	void Update() override final;

	bool GetTec()
	{

		return Technique;
	}

	CVector3 GetPos()
	{

		return m_pos;
	}

private:

	bool Technique = false;		//ãZëIëÇ‹Ç≈èIóπÇµÇΩÇ∆Ç´falseñﬂÇÈÅ@

	CVector3 m_pos = CVector3::Zero();
	GameCursor * m_gamecursor;
	AIEditMode * m_aieditmode;
	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeClick* m_aieditnodeclick;
	SpriteRender * m_spriteRender;

};