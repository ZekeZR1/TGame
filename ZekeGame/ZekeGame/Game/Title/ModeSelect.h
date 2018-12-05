#pragma once
class GameCamera;
class ModeSelect :public GameObject
{
public:
	~ModeSelect();
	bool Start() override;
	void Update() override;
private:
	enum Sel
	{
		enLocalpvp,
		enRandompvp,
		enAIedit,
	};
	std::vector<SpriteRender*> m_selection;
	int m_sel = 0;
	CVector3 m_standardpos = { 100,100,0 };
};