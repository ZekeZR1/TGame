#pragma once
#include "..//GameData.h"
class GameCursor;

class ShowMonsterSkills : public GameObject
{
public :
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
	void SetMonster(MonsterID id) {
		m_monsterId = id;
	}
private:
	void LoadSkillInfo();
	MonsterID m_monsterId;
	SpriteRender* m_backSp = nullptr;
	SpriteRender* m_quitSp = nullptr;
	std::vector<FontRender*> m_defSkillNamesFR;
	std::vector<SpriteRender*> m_sps;
	std::vector<FontRender*> m_monsterSkillNameFR;
	std::vector<FontRender*> m_monsterSkillInfoFR;
	GameCursor* m_cur = nullptr;
	std::wstring m_defSkillNamesStr[6] = { L"çUåÇ",L"í«ê’",L"ì¶ñS",L"éÁÇÈ",L"ì¡éÍ1",L"ì¡éÍ2" };
	std::vector<std::wstring> m_skillInfos;
};

