#pragma once
class AIEditMode;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeClick;
class AIEditLine;
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

	bool Technique = false;		//技選択まで終了したときfalse戻る。　
	bool Click = false;         //クリックが消滅したときにfalseに戻る。

	CVector3 m_pos = CVector3::Zero();
	GameCursor * m_gamecursor;
	AIEditMode * m_aieditmode;
	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeClick* m_aieditnodeclick;
	AIEditLine * m_aieditline;
	SpriteRender * m_spriteRender;

};