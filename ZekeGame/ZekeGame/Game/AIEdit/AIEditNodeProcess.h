#pragma once

class AIEditNode;
class AIEditNodeInequ;
class AIEditNum;
class AIEditNodeProcess :public GameObject
{

public:

	~AIEditNodeProcess();

	bool Start();
	void Update();

private:

	bool NewChoice1 = false;    //AIEditNodeが表示されていない場合。
	bool NewChoice2 = false;    //AIEditNodeInequが表示されていない場合。
	bool NewChoice3 = false;    //AIEditNodeNumが表示されていない場合。

	AIEditNode * m_aieditnode;
	AIEditNodeInequ * m_aieditnodeinequ;
	AIEditNodeNum * m_aieditnodenum;

};