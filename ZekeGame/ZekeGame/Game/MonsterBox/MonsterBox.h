#pragma once
enum MonsterID;

class MonsterBox 
{
public:
	bool isGot(MonsterID id);
	void GetMonster(MonsterID id);
private:
	void CheckMonsterData();
	void WriteFile(int);
	UINT m_monsters = 0;
};

static MonsterBox& IMonsterBox() {
	static MonsterBox monsterBox;
	return monsterBox;
}
