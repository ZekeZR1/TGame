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

	CVector3 m_pos = CVector3::Zero();

	std::vector<FontRender*> m_fonts;

	AIEditNodeTarget* m_aieditnodetarget = nullptr;
	AIEditNode* m_aieditnode = nullptr;
	AIEditNodeInequ* m_aieditnodeinequ = nullptr;
	AIEditNodeNum* m_aieditnodenum = nullptr;
	AIEditNodeTechnique* m_aieditnodetechnique = nullptr;
	AIEditNodeAbnormalState* m_aieditnodeabnormalstate = nullptr;

};