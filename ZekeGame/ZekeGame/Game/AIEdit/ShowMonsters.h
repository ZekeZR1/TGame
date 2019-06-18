#pragma once
class GameCursor;
enum MonsterID;

class ShowMonsters : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetWindowActive(bool active) {
		m_isActive = active;
	}
private:
	void InitFont();
	void InitButtons();
	void InitSideButtons();
	void ButtonUpdate();
	void ChangePage();
	bool m_isActive = true;
	std::vector<SpriteRender*> m_monsterSps;
	std::vector<SpriteRender*> m_frames;
	std::vector<FontRender*> m_MonsterNames;
	std::map<SpriteRender*, MonsterID> m_spId;
	SpriteRender* m_backSp = nullptr;
	SpriteRender* m_quitSp = nullptr;
	SpriteRender* m_leftSp = nullptr;
	SpriteRender* m_rightSp = nullptr;
	const int nX =3;
	const int nY = 7;
	const int nButtonMax= 9;
	CVector3 m_basePos = { -370, 447.5,0 };
	GameCursor* m_cur = nullptr;
	int m_currentPage = 1;
	int m_totalPage = 0;
};

