#pragma once

class Fade :public GameObject
{
public:
	Fade();
	void OnDestroy();

	void Update();

	CVector4 GetMulCol()
	{
		return m_mulcol;
	}
	void SetMulCol(CVector4 col)
	{
		m_mulcol = col;
	}

	void SetSpeed(float sp)
	{
		m_speed = sp;
	}

	void FadeIn()
	{
		m_state = enFadein;
	}
	void FadeOut()
	{
		m_state = enFadeout;
	}

	bool isFadeStop()
	{
		if (m_state == enFadeStop)
		{
			return true;
		}
		return false;
	}
private:
	enum State
	{
		enFadeStop,
		enFadein,
		enFadeout,
	};
	State m_state = enFadeStop;
	SpriteRender* m_black = nullptr;

	CVector4 m_mulcol = { 0,0,0,0 };
	float m_speed = 1;
};