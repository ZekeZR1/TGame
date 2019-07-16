#pragma once
class backParticle : public  GameObject
{
public:
	void SetSpeed(float speed) {
		m_speed = speed;
	}
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	SpriteRender* m_sp = nullptr;
	CVector3 m_pos = CVector3::Zero();
	float m_speed = 0.f;
};

