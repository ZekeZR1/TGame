#pragma once

class Monster;

class MonsterActionList :public GameObject
{
public:
	~MonsterActionList();
	void OnDestroy() override;
	void init(Monster* mon);
	bool Start() override;
	void Update() override;
	void PostRender() override;
private:
	int m_num = 0;
	Monster* m_mon = nullptr;
	SpriteRender* m_back = nullptr;
	SpriteRender* m_icon = nullptr;
	std::vector<SpriteRender*> m_actBlocks;
	int m_len = 0;

	FontRender* m_frs[3];
	FontRender* m_Sfrs[3];

	SpriteRender* m_hp = nullptr;
	SpriteRender* m_mp = nullptr;

	FontRender* m_fhp = nullptr;
	FontRender* m_fmp = nullptr;
	FontRender* m_Sfhp = nullptr;
	FontRender* m_Sfmp = nullptr;

	CVector2 m_vh = CVector2::Zero();
	CVector2 m_vm = CVector2::Zero();

	SpriteRender* m_monNumBack = nullptr;
	FontRender* m_monNum = nullptr;
	FontRender * m_SmonNum = nullptr;

	FontRender* m_SHPfr = nullptr;
	FontRender* m_SMPfr = nullptr;
	FontRender* m_HPfr = nullptr;
	FontRender* m_MPfr = nullptr;
	const float yfix = 10.f;
};