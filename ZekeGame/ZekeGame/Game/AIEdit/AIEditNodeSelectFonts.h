#pragma once
class AIEditNodeTarget;
class AIEditNode;
class AIEditNodeInequ;
class AIEditNodeNum;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class AIEditNodeSelectFonts : public GameObject
{
public:

	~AIEditNodeSelectFonts();

	bool Start();
	void Update();
	void FontsDisplay();

private:

	bool target = true;
	bool node = true;
	bool inequ = true;
	bool num = true;
	bool technique = true;
	bool abnormal = true;
	float scale = 0.8;

	std::vector<FontRender*> m_fonts;
	CVector3 m_pos = CVector3::Zero();

	AIEditNodeTarget* m_aieditnodetarget;
	AIEditNode* m_aieditnode;
	AIEditNodeInequ* m_aieditnodeinequ;
	AIEditNodeNum* m_aieditnodenum;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate;

};