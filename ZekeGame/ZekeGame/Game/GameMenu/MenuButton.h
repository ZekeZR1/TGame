#pragma once

class GameCursor;
class MenuButton :public GameObject
{
public:
	~MenuButton();
	bool Start() override;
	void init(GameCursor* cursor,CVector3 pos,SpriteRender* moji=nullptr)
	{
		m_cursor = cursor;
		m_pos = pos;
		m_moji = moji;
	}

	void Update() override;

	bool isClick()
	{
		return m_isClick;
	}
private:
	SpriteRender* m_button = nullptr;
	SpriteRender* m_dummy = nullptr;

	SpriteRender* m_moji = nullptr;

	CVector3 m_pos = CVector3::Zero();

	bool m_isSelect = false;
	bool m_isClick = false;

	GameCursor* m_cursor = nullptr;
};