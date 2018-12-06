#pragma once

class ResultCamera :public GameObject
{
public:
	~ResultCamera();
	bool Start();
	void Update();
	void SetPos(CVector3 v)
	{
		m_pos = v;
	}
	void SetTar(CVector3 v)
	{
		m_tar = v;
	}
	CVector3 GetPos()
	{
		return m_pos;
	}
	CVector3 GetTar()
	{
		return m_tar;
	}

private:
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_tar = CVector3::Zero();
};