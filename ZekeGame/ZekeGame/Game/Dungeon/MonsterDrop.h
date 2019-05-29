#pragma once

class DropEgg;

class MonsterDrop : public GameObject
{
public:
	MonsterDrop();
	~MonsterDrop();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void setDungeonNum(int n) {
		m_stage = n;
	}
private:
	void InitUI();
	void Notifications();
	void InitModels();
	void SceneTransition();
	void ToDungeonSelect();
	
	int m_stage = 0;
	DropEgg* m_egg = nullptr;
	SkinModelRender* m_back = nullptr;
	CVector3 m_backPosition = { 0.f,0.f,-300.f };
	//UI
		//next
	FontRender* m_nextfont = nullptr;
		//notify
	SpriteRender* m_notifySp = nullptr;
	CVector3 m_notifyLinePos = { 0.f,300.f,0.f };
	FontRender* m_notifyFont = nullptr;
	bool m_isInited = false;
		//name
	SpriteRender* m_monsterNameSp = nullptr;
	//Fade
	Fade* m_fade = nullptr;
	bool m_fadeFlag = false;
	//other
	Sound* m_BGM = nullptr;
};

