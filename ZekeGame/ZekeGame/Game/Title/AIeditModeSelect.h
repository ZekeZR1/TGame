#pragma once

class Fade;
class AIEditModeSelect :public GameObject
{
public:
	~AIEditModeSelect();
	bool Start();
	void Update();
private:
	enum AIMode
	{
		enVisual,
		enPython,
		
	};
	SpriteRender* m_spMode[2];

	int m_sel = 0;

	Fade* m_fade;

};