#pragma once
#include "../GameData.h"
class GameCursor;
class MonsterSelect;
class AISelect;
class PMMonster :public GameObject
{
public:
	~PMMonster();
	PMMonster();
	bool Start() override;
	void init(int num, CVector3 pos);
	void Update() override;

	//Update‚³‚ê‚È‚¢Update
	void UpdateEX();

	void Open();
	void ChengeImage(int monid);
	void SetPython(const wchar_t* py,int num,int AImode);

	void yesSelect();
	void notSelect();
	bool isSelect()
	{
		return m_issel;
	}

	void PostRender() override;

	int GetMonsterID()
	{
		return (int)m_monid;
	}

	void SetMonsterID(MonsterID monid) {
		m_monid = monid;
	}
	void SetAI(int ai) {
		m_selAI;
	}

	int GetAI()
	{
		return m_selAI;
	}
	int GetAImode()
	{
		return m_AImode;
	}

	int Getnum()
	{
		return m_num;
	}

	void Setteam(int team)
	{
		m_team = team;
	}
	int Getteam()
	{
		return m_team;
	}

	bool isMonSel()
	{
		return m_ismonsel;
	}
	void notMonSel()
	{
		m_ismonsel = false;
	}

	bool isOpen()
	{
		return m_isOpen;
	}
	void Close()
	{
		m_isOpen = false;
	}
	bool isClick()
	{
		return m_isClick;
	}
private:
	int m_num = 0;
	int m_team = 0;
	MonsterID m_monid = enTest;
	int m_selAI = 0;
	int m_AImode = 0;						//python‚È‚Ì‚©VisualScript‚È‚Ì‚©

	GameCursor* m_cursor = nullptr;
	MonsterSelect* m_ms = nullptr;
	AISelect* m_ais = nullptr;

	SpriteRender* m_frame = nullptr;
	bool m_issel = false;
	SpriteRender* m_mon = nullptr;
	const wchar_t* m_path;

	bool m_ismonsel = false;

	CVector3 m_mickey = CVector3::Zero();

	wchar_t m_python[16] = L"testBrain";
	CFont font;
	FontRender* m_fr = nullptr;
	FontRender* m_frShadow = nullptr;

	bool m_isClick = false;
	bool m_isOpen = false;
};