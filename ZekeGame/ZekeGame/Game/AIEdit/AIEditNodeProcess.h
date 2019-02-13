#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNum;
class AIEditNodeNum;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeTarget;
class AIEditNodeClick;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();
	void ButtonPosition();

	enum State
	{
		FirstOrder,
		SecondOrder,
		LastOrder

	};

private:

	bool NewChoice1 = false;    //AIEditNodeが表示されていない場合。
	bool NewChoice2 = false;    //AIEditNodeInequが表示されていない場合。
	bool NewChoice3 = false;    //AIEditNodeNumが表示されていない場合。
	bool OrderChoice = false;   //AIEditNodeOrderが表示されていないとき

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNodeClick* m_aieditnodeclick;
	SpriteRender * m_spriteRender;

};