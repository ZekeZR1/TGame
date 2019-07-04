#pragma once
class DropEgg : public GameObject
{
public:
	DropEgg();
	~DropEgg();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	MonsterID GetMonsterID() {
		return m_monsterId;
	}
	wchar_t* GetMonsterName(){
		return m_monsterName;
	}
	void SetDropMonster(MonsterID id) {
		m_monsterId = id;
	}

private:
	CEffect* ef = nullptr;
	CQuaternion rot = CQuaternion::Identity();
	void NewMonster();
	//Monster
	SkinModelRender* m_monster = nullptr;
	CVector3 m_monsterPos = { 0.f,-200.f,-200.f };
	CVector3 m_modelScale = { 1.5f,1.5f ,1.5f };
	CQuaternion m_monsterRot = CQuaternion::Identity();
	AnimationClip m_animClip[1];
	//Egg
	SkinModelRender* m_egg = nullptr;
	CVector3 m_eggPos = { 0.f,-100.f,-200.f };
	CVector3 m_eggSca = CVector3::One();
	CQuaternion m_eggRot = CQuaternion::Identity();
	//efk
	CEffect* m_efk;
	//other
	float m_timer = 0.f;
	bool mflag_eggbig = true;
	float mf_eggSca = 1.f;
	bool mb_efk = false;
	bool m_isPlayedEffect = false;
	bool m_isPlayedBackEffect = false;
	bool m_isDisplayMonster = false;
	MonsterID m_monsterId;
	wchar_t m_monsterName[256] = { L"?" };
	float m_eggTime = 0.f;
};

