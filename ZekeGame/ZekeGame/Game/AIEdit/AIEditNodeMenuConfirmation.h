#pragma once

class GameCursor;
class AIEditNodeMenu;
class AIEditNodeMenuConfirmation : public GameObject
{

public:
	~AIEditNodeMenuConfirmation();

	bool Start();
	void Update();


private:

	int button = 2;

	std::vector<SpriteRender*> sp;
	std::vector<SpriteRender*> m_buttons;
	std::vector<FontRender*> m_fonts;
	FontRender* m_fonts2;

	GameCursor* m_gamecursor;
	SpriteRender* m_spriteRender;
	AIEditNodeMenu* m_aieditnodemenu;
	CVector3 confpos = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	CVector2 m_fontpos = CVector2::Zero();
	CVector2 m_fontpos2 = CVector2::Zero();



};



