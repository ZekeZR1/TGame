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

enum eTarget {

	enme = 100,
	enbaddy,
	enenemy,
	enTAnull = 0,
};

enum eNode {

	enHp = 200,
	enMp,
	enAb,
	enTechnique,
	enNonull = 0,
};

enum eInequ {

	enDainari = 300,
	enShowers,
	enINnull = 0,
};

enum eNum {

	en1 = 400,
	en10,
	en30,
	en50,
	en70,
	en90,
	en100,
	enNUnull = 0

};

enum eTechnique {

	enAttak = 500,
	enLeav,
	enCase,
	enProtect,
	enHeel,
	enSpecial1,
	enSpecial2,
	enTEnull = 0,
};

enum eAbnormal {

	endoku = 600,
	enyakedo,
	enhyouketu,
	ensutan,
	enABnull = 0,
};

struct sOrder
{
	eTarget tar = enTAnull;
	eNode nod = enNonull;
	eInequ ine = enINnull;
	eNum num = enNUnull;
	eTechnique tec = enTEnull;
	eAbnormal abn = enABnull;
};

class AIEditNodeOrder :public GameObject
{

public:

	~AIEditNodeOrder();
	void OnDestroy();
	
	bool Start() override final;
	void Update() override final;
	void DeleteGOs();
	void Fonts();
	void makeOrder(int l,int o,sOrder* order,bool isEnd=false);
	void makeFonts(sOrder* order);
	
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

	bool isTechniqueOrder()
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

	int num = 1;
	int fonttimer = 25;          //上に表示されている確認用のfontを

	bool Technique = false;		//技を選択したときtrueになる。　
	bool techniqueOrder = false;
	bool timer = false;
	bool key = false; //deletekeyに何かが入ったらtrueになる。
	bool NextClickFlag = false;  //Deletekeyを使って列をDeleteしたと気にtrueになる。
	bool m_isMakeOrder = false;				//makeOrderした場合はStart等を無視するためのフラグ

	float scale = 0.7;          //fontのスケール。
	
	CVector3 m_pos = CVector3::Zero();

	AIEditNodeDeleteKey* m_keepdelete[8];

	std::vector<FontRender*> m_fonts;

	SpriteRender* m_spriteRender = nullptr;

	GameCursor * m_gamecursor = nullptr;
	AIEditMode * m_aieditmode = nullptr;
	AIEditNode * m_aieditnode = nullptr;
	AIEditNodeInequ * m_aieditnodeinequ = nullptr;
	AIEditNodeNum * m_aieditnodenum = nullptr;
	AIEditNodeClick* m_aieditnodeclick = nullptr;
	AIEditLine * m_aieditline = nullptr;
	AIEditNodeTarget* m_aieditnodetarget = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeTechnique* m_aieditnodetechnique = nullptr;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate = nullptr;
	AIEditNodeSelectFonts* m_aieditonodeselectfonts = nullptr;
	AIEditNodeDeleteKey* m_aieditnodedeletekey = nullptr;

};