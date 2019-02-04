#pragma once

class Monster;

class MonsterActionList :public GameObject
{
public:
	~MonsterActionList();
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

	SpriteRender* m_hp = nullptr;
	SpriteRender* m_mp = nullptr;

	FontRender* m_fhp = nullptr;
	FontRender* m_fmp = nullptr;

	CVector2 m_vh = CVector2::Zero();
	CVector2 m_vm = CVector2::Zero();
};