#pragma once
enum MonsterID;

class MonsterBox 
{
public:
	bool isGot(MonsterID id);
	void GetMonster(MonsterID id);
	static MonsterBox& GetInstance() {
		static MonsterBox instance;
		return instance;
	}

private:
	void initFile();
	void LoadMyBox();
	int m_monsters[500] = { 0 };
};

static MonsterBox& IMonsterBox() {
	return MonsterBox::GetInstance();
}
