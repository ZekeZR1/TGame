#pragma once

class Fade :public GameObject
{
public:
	Fade();
	void OnDestroy();

	void Update();

	//乗算色のゲット
	CVector4 GetMulCol()
	{
		return m_mulcol;
	}

	//乗算色のセット。
	void SetMulCol(CVector4 col)
	{
		m_mulcol = col;
	}

	//フェードスピードのゲット。
	float GetSpeed()
	{
		return m_speed;
	}
	//フェードスピードのセット。
	void SetSpeed(float sp)
	{
		m_speed = sp;
	}

	//フェードイン
	void FadeIn()
	{
		m_state = enFadein;
	}
	//フェードアウト
	void FadeOut()
	{
		m_state = enFadeout;
	}

	//今フェードは止まっているか？
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
	State m_state = enFadeStop;			//フェードの状態
	SpriteRender* m_black = nullptr;	//フェードのスプライト　ブラックとなっているが、その実こいつに使われている画像は1x1の白い画像なのだ。

	CVector4 m_mulcol = { 0,0,0,0 };	//スプライトにかける色
	float m_speed = 1;					//フェードのスピード 1だとデルタタイムがそのまま入る。
};