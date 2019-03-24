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
class AIEditNodeSelectFonts;
class AIEditNodeDeleteKey;
class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	
	bool Start() override final;
	void Update() override final;
	void DeleteGOs();
	void Fonts();
	void DeletekeyClick();
	
	AIEditNodeDeleteKey* CreateDeleteKey();

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

	bool GettechniqueOrder()
	{

		return techniqueOrder;
	}

	bool GetNextClickFlag()
	{
		return NextClickFlag;
	}

	void SetNextClickFlag(bool a)
	{
		NextClickFlag = a;
	}


private:

	bool Technique = false;		//技を選択したときtrueになる。　
	bool techniqueOrder = false;
	bool timer = false;
	bool key = false; //deletekeyに何かが入ったらtrueになる。
	int num = 1;
	int fonttimer = 25;          //上に表示されている確認用のfontを
	float scale = 0.7;          //fontのスケール。
	bool NextClickFlag = false;  //Deletekeyを使って列をDeleteしたと気にtrueになる。

	AIEditNodeDeleteKey* m_keepdelete[8];

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
	AIEditNodeSelectFonts* m_aieditonodeselectfonts;
	AIEditNodeDeleteKey* m_aieditnodedeletekey;

};