#pragma once

class GameCursor :public GameObject
{
public:
	~GameCursor();
	bool Start() override;
	void Update() override;

	CVector3& GetCursor()
	{
		return m_pos;
	}
private:
	SpriteRender* m_cursor = nullptr;
	CVector3 m_pos = CVector3::Zero();
};

 static inline void PlayButtonSE() {
	auto se = NewGO<Sound>(0);
	se->Init(L"Assets/sound/se/button.wav", false);
	se->Play();
}