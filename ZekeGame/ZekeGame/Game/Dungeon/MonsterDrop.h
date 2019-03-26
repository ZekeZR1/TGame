#pragma once
class MonsterDrop : public GameObject
{
public:
	MonsterDrop();
	~MonsterDrop();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	void NewMonster();
	void InitUI();
	void InitModels();
	void SceneTransition();
	void ToDungeonSelect();
	void EggPfm();
	CVector3 m_modelScale = { 1.5f,1.5f ,1.5f };
	SpriteRender* m_nextButtonSp = nullptr;
	SpriteRender* m_notifySp = nullptr;
	SpriteRender* m_monsterNameSp = nullptr;
	CVector3 m_nextButtonPos = { 460.f,-200.f,0.f };
	CVector3 m_notifyLinePos = { 0.f,300.f,0.f };
	CVector3 m_backPosition = { 0.f,0.f,-300.f };
	CVector3 m_eggPos = { 0.f,-100.f,0.f };
	CQuaternion m_eggRot = CQuaternion::Identity();
	SkinModelRender* m_monster = nullptr;
	SkinModelRender* m_egg = nullptr;
	SkinModelRender* m_back = nullptr;
	CVector3 m_monsterPos = { 0.f,-100.f,0.f };
	CQuaternion m_monsterRot = CQuaternion::Identity();
	GameCursor* m_cursor = nullptr;
	Fade* m_fade = nullptr;
	MonsterID m_monsterId;
	bool m_fadeFlag = false;
	AnimationClip m_animClip[1];
	FontRender* m_notifyFont = nullptr;
	float m_timer = 0.f;
	int m_eggnum = 0;
	CEffect* m_efk;
	bool mflag_eggbig = true;
	CVector3 m_eggSca = CVector3::One();
	float mf_eggSca = 1.f;
	bool mb_efk = false;
	bool m_isPlayedEffect = false;
	bool m_isDisplayMonster = false;
	float m_eggTime = 0.f;
};

