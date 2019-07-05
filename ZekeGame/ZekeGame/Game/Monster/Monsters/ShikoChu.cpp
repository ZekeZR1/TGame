#include "stdafx.h"
#include "ShikoChu.h"

#include "../../GameData.h"

ShikoChu::ShikoChu()
{

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/si_bug.cmo");
	//sr->SetScale(CVector3::One() * 20);

	sr->SetPosition(CVector3::Zero());

	MonsterInitParam prm;
	prm.HP = 60;
	prm.MP = 30;
	prm.DefencePow = 10;
	prm.ExDefensePow = 5;
	prm.AttackPow = 10;
	prm.ExAttackPow = 30;
	prm.Speed = 50;
	prm.Radius = 50;
	prm.Height = 150;
	prm.ModelRender = sr;
	prm.NumAnimation = 0;
	init(prm);

	m_ID = enShikoChu;
	int cnt = 0;
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	
}
