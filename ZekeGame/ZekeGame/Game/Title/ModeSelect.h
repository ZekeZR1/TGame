#pragma once
class GameCamera;
class GameCursor;
class Fade;
class ModeSelectBack;
struct button
{
	button()
	{
		frame = NewGO<SpriteRender>(2, "sp");
		frame->Init(L"Assets/sprite/modesel_frame.dds", 690, 150,true);
		
		//moji = NewGO<SpriteRender>(3, "sp");
		font = NewGO<FontRender>(3, "fr");
		font->SetTextType(CFont::en_JapaneseBIG);
	}
	~button()
	{
		DeleteGO(frame);
		//DeleteGO(moji);
		DeleteGO(font);
	}
	SpriteRender* frame = nullptr;
	SpriteRender* moji = nullptr;
	FontRender* font = nullptr;
	bool isCursor = false;
};

class ModeSelect :public GameObject
{
public:
	~ModeSelect();
	bool Start() override;
	void Update() override;
private:
	enum Sel
	{
		enDungeon,
		enLocalpvp,
		enRandompvp,
		enAIedit,
	};
	CVector2 m_bSize = { 690,150 };
	std::vector<button*> m_buttons;
	CVector2 m_butoffs = { -260,50 };

	std::vector<SpriteRender*> m_selection;
	int m_sel = 0;
	CVector3 m_standardpos = { 390,80,0 };

	SpriteRender* m_back = nullptr;

	GameCursor* m_cursor = nullptr;
	int m_count = 0;

	Sound* m_BGM = nullptr;

	Fade* m_fade = nullptr;
	bool m_isfade = false;
	int m_mode = enDungeon;

	ModeSelectBack* m_msBack = nullptr;			//haikei
};