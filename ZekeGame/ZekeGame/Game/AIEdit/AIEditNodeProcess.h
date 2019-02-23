#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeTarget;
class AIEditNodeClick;
class AIEditNodeTechnique;
class AIEditNodeMenu;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();
	void ButtonPosition();
	void Click();
	void Target();
	void Technique();
	


	bool GetTheOrder()
	{

		return m_state;
	}

	void SetTheOrderNum(bool a)
	{

		StateNum = a;
	}

	void enSecond()
	{

		m_state = enSecondOrder;
	}

	bool GetClickFlag()
	{
		return Clickflag;
	}

	void SetClickFlag(bool a)
	{
		Clickflag = a;
	}

	int GettechniqeCount()
	{
		return TechniqueCount;
	}


private:

	int StateNum = 1;
	
	int num = 0;
	int TechniqueCount = 0;
	bool Clickflag = 0;

	bool Choice1 = false;    
	bool Choice2 = false;   
	bool Choice3 = false;    
	bool Choice4 = false;    
	bool Choice5 = false;    
	bool Choice6 = false;    
	bool Choice7 = false;    
	bool Choice8 = false;    
	bool OrderChoice = false;   //AIEditNodeOrderÇ™ï\é¶Ç≥ÇÍÇƒÇ¢Ç»Ç¢Ç∆Ç´

	enum State
	{
		enFirstOrder,     //clickÇÇ®ÇµÇΩéûÇÃèàóù
		enSecondOrder,
		enThirdOrder,
		enFourthOrder,
		enFifthOrder,
		enSixthOrder,
		enSeventhOrder,
		enEighthOrder

	};

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeClick* m_aieditnodeclick;
	SpriteRender * m_spriteRender;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeMenu* m_aieditnodemenu;

	State m_state = enFirstOrder;

};