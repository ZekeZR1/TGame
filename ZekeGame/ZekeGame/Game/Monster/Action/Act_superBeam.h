#pragma once
#include "../MonsterAction.h"

class Act_superBeam : public MonsterAction
{
public:
	Act_superBeam();
	bool Action(Monster* me) override;
private:
	int m_cost = 50;
	bool m_first = true;
	CVector3 m_efPos = CVector3::Zero();
	CVector3 m_laserVec = CVector3::Zero();
	CEffect* m_efk = nullptr;
	CVector3 m_efs = { 5,5,5 };
	float m_laserTheta = 0.f;
	float m_nearTheta = 5.f;
};

