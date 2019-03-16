#pragma once

class GameCursor;
AIEditNodeMenu;
class AIEditNodeMenuWindow : public GameObject
{

public:

	~AIEditNodeMenuWindow();

	bool Start();
	void Update();

private:

	int button = 3;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	std::vector<SpriteRender*> m_buttons;
	std::vector<FontRender*> m_fonts;

	std::vector<SpriteRender*> sp;
	SpriteRender* m_spriteRender;

	SpriteRender* m_spriterender2;
	GameCursor* m_gamecurosor;
	AIEditNodeMenu* m_aieditnodemenu;

};