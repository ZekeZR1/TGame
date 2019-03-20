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
	void SceneTransition();
	void ToDungeonSelect();
	SpriteRender* m_nextButtonSp = nullptr;
	SpriteRender* m_notifySp = nullptr;
	SpriteRender* m_monsterNameSp = nullptr;
	CVector3 m_nextButtonPos = { 460.f,-200.f,0.f };
	CVector3 m_notifyLinePos = { 0.f,300.f,0.f };
	SkinModelRender* m_monster = nullptr;
	SkinModelRender* m_egg = nullptr;
	SkinModelRender* m_back = nullptr;
	CVector3 m_monsterPos = CVector3::Zero();
	CQuaternion m_monsterRot = CQuaternion::Identity();
	GameCursor* m_cursor = nullptr;
	Fade* m_fade = nullptr;
	MonsterID m_monsterId;
	bool m_fadeFlag = false;
	AnimationClip m_animClip[1];
	FontRender* m_notifyFont = nullptr;
};

