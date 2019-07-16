#pragma once
//HTC VIVE
class GameCursor;
class DungeonResult :public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void init(int team, int num)
	{
		m_team = team;
		m_dunNum = num;
	}
private:
	void SaveDungeonClearState();
	void ToNextRound();
	void ToNextStage();
	void ToDungeonSelect();
	void ToMonsterDrop();
	void InitUI();
	void Lose();
	void MonsterSet();
	void CameraSet();
	void ButtonUpdate();
	void CameraUpdate();
	int m_team = 0;
	int m_dunNum = -1;
	ResultCamera* m_cam = nullptr;
	FontRender* m_nextfont = nullptr;
	SpriteRender* m_srwin = nullptr;
	SpriteRender* m_srteam = nullptr;
	Sound* m_BGM = nullptr;
	CVector3 m_firstpos = CVector3::Zero();
	CVector3 m_firsttar = CVector3::Zero();
	CVector3 m_lastpos = CVector3::Zero();
	CVector3 m_lasttar = CVector3::Zero();
	CVector3 m_addpos = CVector3::Zero();
	CVector3 m_addtar = CVector3::Zero();
	bool m_cmove = true;
	bool m_fadeFlag = false;
	Fade* m_fade = nullptr;
	static const int WIN = 0;
};