#include "stdafx.h"
#include "ShikoChu.h"

#include "../../GameData.h"

ShikoChu::ShikoChu()
{

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/si_bug.cmo");
	//sr->SetScale(CVector3::One() * 20);

	sr->SetPosition(CVector3::Zero());
	init
	(
		//160,
		80,
		30,
		10,
		0,
		10,
		0,
		10,
		50,
		150,
		sr,
		0
	);
	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	SetUseAction(ua, 2);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	m_ID = enShikoChu;
}
