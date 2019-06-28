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

	CVector2 m_fontpos = CVector2::Zero();
	CVector2 m_fontpos2 = CVector2::Zero();

	CVector3 confpos = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();

	std::vector<SpriteRender*> sp;
	std::vector<SpriteRender*> m_buttons;
	std::vector<FontRender*> m_fonts;

	FontRender* m_fonts2 = nullptr;
	SpriteRender* m_spriteRender = nullptr;

	GameCursor* m_gamecursor = nullptr;
	AIEditNodeMenu* m_aieditnodemenu = nullptr;

};



