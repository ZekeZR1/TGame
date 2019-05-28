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

	//flagkeepとorderkeepを消す
	void DeleteAll();
	AIEditNodeOrder* CreateOrder();
	
	void AISave(int num,int col);

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

	bool GetTechniqueGenerate()
	{
		return TechniqueGenerate;
	}

	void SetTechniqueGenerate(bool a)
	{
		TechniqueGenerate = a;
	}

	//ここから下で各クラスのenumを保存していく。

	//ターゲットを保持。
	void Setkeeptarget(int n)
	{
		flagkeep[keep1][keep2][0] = n;
	}

	//nodeを保持。
	void Setkeeonode(int n)
	{
		flagkeep[keep1][keep2][1] = n;
	}

	//＜＞を保持。
	void Setkeepinequ(int n)
	{
		flagkeep[keep1][keep2][2] = n;
	}

	//数値(％)を保持。
	void Setkeepnum(int n)
	{
		flagkeep[keep1][keep2][3] = n; 
		keep2 += 1;
	}

	//状態異常を保持。
	void Setkeepabnormal(int n)
	{
		flagkeep[keep1][keep2][4] = n;
		keep2 += 1;
	}

	//技を保持。
	void Setkeeptechnique(int n);

	void setOrderkeep(int l,int o,AIEditNodeOrder* order)
	{
		m_orderkeep[l][o] = order;
	}

	/*
	flagkeep にセットする
	arg:
		y:Y軸
		x:X軸
		k:種類
			0 = target
			1 = node
			2 = inequ
			3 = num
			4 = abnormal
			5 = technique
		v:値
	*/
	void setFlagkeep(int y, int x, int k, int v)
	{
		flagkeep[y][x][k] = v;
	}

	//flagkeepの値を全部０にする
	void allDeleteFlagkeep()
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				for (int k = 0; k < 6; k++)
				{
					flagkeep[y][x][k] = 0;
				}
			}
		}
	}

	//クリックをクリックした
	void ClickClicking()
	{
		m_isClickClicked = true;
	}

	//クリックをクリックしたかどうか
	bool isClickClicked()
	{
		return m_isClickClicked;
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
	float ClickePosY = 275;				//AIEditNodeClickをNewするときのY座標。
	bool Clickflag = 0;
	bool OrderChoice = false;			//AIEditNodeOrderが表示されていないとき。
	bool TechniqueGenerate = false;		//techniqueが表示されるとtrueになる。deletekeyで使う。

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

	bool m_isClickClicked = false;		//クリックがクリックされたか
};