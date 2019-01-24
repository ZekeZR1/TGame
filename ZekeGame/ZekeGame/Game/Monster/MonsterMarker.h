#pragma once

class Monster;
class MonsterMarker :public GameObject
{
public:
	~MonsterMarker();
	bool Start() override;
	void init(Monster* mon);
	void Update() override;
private:
	SpriteRender* m_marker = nullptr;
	SpriteRender* m_number = nullptr;
	Monster* m_mon = nullptr;
};