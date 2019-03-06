#pragma once

class ResultCamera;
class Win:public GameObject
{
public:
	Win(int team);
	Win();
	~Win();
	void OnDestroy() override;
	void init(int team);
	bool Start();
	void Update();

	void MonsterSet();
	void CameraSet();

	
private:
	ResultCamera* m_cam = nullptr;
	int m_team = 0;
	SpriteRender* m_sr = nullptr;

	CVector3 m_firstpos = CVector3::Zero();
	CVector3 m_firsttar = CVector3::Zero();

	CVector3 m_lastpos = CVector3::Zero();
	CVector3 m_lasttar = CVector3::Zero();

	CVector3 m_addpos = CVector3::Zero();
	CVector3 m_addtar = CVector3::Zero();

	bool m_cmove = true;

	SpriteRender* m_srwin = nullptr;
	SpriteRender* m_srteam = nullptr;

	Sound* m_BGM = nullptr;
};