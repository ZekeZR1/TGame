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
class AIEditNodeSelectButtons;
class AIEditNodeDeleteKey;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();
	void Click();
	void Target();
	void Technique();
	void DeleteKey(AIEditNodeOrder* a);
	AIEditNodeOrder* CreateOrder();
	

	void AISave();

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

	//ここから下で各クラスのenumを保存していく。
	void Setkeeptarget(int n)
	{
		flagkeep[keep1][keep2][0] = n;
	}

	void Setkeeonode(int n)
	{
		flagkeep[keep1][keep2][1] = n;
	}

	void Setkeepinequ(int n)
	{
		flagkeep[keep1][keep2][2] = n;
	}

	void Setkeepnum(int n)
	{
		flagkeep[keep1][keep2][3] = n; 
		keep2 += 1;
	}

	void Setkeepabnormal(int n)
	{
		flagkeep[keep1][keep2][4] = n;
		keep2 += 1;
	}

	void Setkeeptechnique(int n)
	{
		flagkeep[keep1][keep2][5] = n;
		keep1 += 1;
		keep2 = 0;
	}

private:

	int flagkeep[8][3][6];   //各クラスで何を選択したかを保持しておくためのもの。
	int keep1 = 0; //８行ある内の何個目か。
	int keep2 = 0; //３列のうちの何個目か。
	int keep3 = 0; /*どのクラスを選択したか。 0 = target
				                              1 = node
											  2 = inequ
											  3 = num
											  4 = abnormal
											  5 = technique 　　*/

	AIEditNodeOrder* m_orderkeep[8][3];

	int StateNum = 1;
	
	int num = 0;
	int TechniqueCount = 0;
	float ClickePosY = 275;     //AIEditNodeClickをNewするときのY座標。
	bool Clickflag = 0;
	bool OrderChoice = false;   //AIEditNodeOrderが表示されていないとき。


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
	AIEditNodeSelectButtons* m_aieditnodeselectbuttons;
	AIEditNodeDeleteKey* m_aieditnodedeletekey;

};