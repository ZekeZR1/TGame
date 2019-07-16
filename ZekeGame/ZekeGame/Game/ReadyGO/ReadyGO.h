#pragma once

class ReadyGO :public GameObject
{
public:
	~ReadyGO();
	bool Start();
	void Update() override;
	void GO();

	bool IsEnd()
	{
		return isEnd;
	}
private:
	bool isEnd = false;

	SpriteRender* m_ready = nullptr;
	CVector3 m_rpos = CVector3::Zero();
	float m_rScale = 0.0f;
	float m_rAlpha = 0.1f;

	SpriteRender* m_GO = nullptr;
	CVector3 m_gpos = CVector3::Zero();
	float m_gScale = 0.1;
	float m_gAlpha = 1;

	bool isFirstGO = true;
};