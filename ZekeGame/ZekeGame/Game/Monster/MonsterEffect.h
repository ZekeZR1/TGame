#pragma once
class Monster;

enum Motion
{
	en_front,
	en_rotate,
	en_left,
	en_right,
};
class MonsterEffect :public GameObject
{
public:
	~MonsterEffect();
	void init(const wchar_t* path,Motion motion,Monster* me,CVector3 offset,CVector3 scale);
	void Update() override final;

	void MFront();
	void MRotate();
	void MLeft();
	void MRight();

	bool IsPlay();

	
private:
	CEffect* m_effect = nullptr;
	Monster* m_me = nullptr;
	CVector3 m_offset = CVector3::Zero();
	CVector3 m_scale = CVector3::Zero();

	Motion m_motion = en_front;
};