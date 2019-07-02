#include "stdafx.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "MonsterEffect.h"
#include "../PythonBridge/PythonBridge.h"
#include "../../Engine/character/CharacterController.h"

#include "../GameData.h"
//#include "MonsterAI.h"

#include "MonsterActionList.h"
#include "MonsterMarker.h"

#include "Action/ACTEffect.h"

Monster::~Monster()
{
	DeleteGO(m_smr);
	DeleteGO(m_PB);
	ReleaseMAL();
	ReleaseMark();
	for (auto a : m_abnormalStates)
		DeleteGO(a);
	for (auto a : m_actions)
		DeleteGO(a);
	delete[] m_UseAction;
	delete m_pyFile;
	delete m_visualAI;
}

void Monster::ReleaseMAL()
{
	if (!m_dmal)
	{
		DeleteGO(m_MAL);
		m_dmal = true;
	}
}

void Monster::ReleaseMark()
{
	if (m_marker != nullptr)
	{
		DeleteGO(m_marker);
		m_marker = nullptr;
	}
}

void Monster::init(MonsterInitParam param) {
	init(
		param.HP,
		param.MP, 
		param.DefencePow, 
		param.ExDefensePow, 
		param.AttackPow, 
		param.ExAttackPow,
		param.Speed,
		param.Radius,
		param.Height,
		param.ModelRender,
		param.NumAnimation
	);
}

void Monster::init(float HP, float MP,float Defense,float ExDefense, float Attack, float ExAttack, float speed, float radius, float height, SkinModelRender * smr, int animnum)
{
	m_HP = HP;
	m_maxHP = HP;
	m_MP = MP;
	m_maxMP = MP;

	m_Defense = Defense;
	m_ExDefense = ExDefense;

	m_Attack = Attack;
	m_ExAttack = ExAttack;

	m_speed = speed;
	m_radius = radius;
	m_height = height;
	m_smr = smr;
	m_AnimNum = animnum;
}

void Monster::SetUseAction(ActionID* ua,int size)
{
	m_UseAction = ua;
	m_useActionSize = size;
}

void Monster::SuddenDeath()
{
	float hp = m_HP * 0.3f;
	m_HP = hp;
	m_maxHP = hp;
}

bool Monster::Start()
{
	m_smr->SetPosition(m_pos);
	m_cc.Init(m_radius, m_height, m_pos,enFbxUpAxisY);
	m_PB = NewGO<PythonBridge>(0,"PB");

	anim_idle();

	m_MAL = NewGO<MonsterActionList>(0, "mal");
	m_MAL->init(this);

	m_marker = NewGO<MonsterMarker>(0, "mark");
	m_marker->init(this);

	if (m_team == 0)
	{
		CQuaternion q = CQuaternion::Identity();
		q.SetRotationDeg(CVector3::Up(), 180);
		m_smr->SetRotation(q);
	}
	return true;
}

void Monster::Update()
{
	if (m_end)
		return;
	if (m_HP <= 0)
	{
		CEffect* eff = NewGO<CEffect>(0, "ef");
		CVector3 efp = m_pos;
		efp.y += m_height/2;
		eff->SetPosition(efp);
		eff->SetScale({ 3,3,3 });
		eff->Play(L"Assets/effect/PONG.efk",2);

		Sound* se = NewGO<Sound>(0, "se");
		se->Init(L"Assets/sound/ani_fa_mon07.wav");
		se->Play();

		m_state = en_Dead;
		GameData::deletemons(this);
		DeleteGO(this);
	}
	switch (m_state)
	{
	case en_NowLoading:
		if (m_actionTime > 2)
		{
			//m_PB->py_exe(m_num, m_team, m_pyFile);
			if (!isLoading)
			{
				if (!m_isUseVSAI)
					PythonBridge::py_exe(m_num, m_team, m_pyFile->c_str());
				else
					m_visualAI->Run();
				//m_PB->py_exeEX(m_num, m_team, m_pyFile);
				//isLoading = true;
			}
			if (m_actions.size() >= 1)
			{
				m_state = en_Execute;
				isLoading = false;
			}
			m_actionTime = 0;
			if (!m_smr->IsPlayingAnimation())
			{
				anim_idle();
			}
		}
		break;
	case en_Execute:
	{
		bool isAbnormal = true;
		for (auto as : m_abnormalStates)
		{
			if (as->GetAbnormalState() == abStan)
			{
				isAbnormal = false;
				m_movespeed = CVector3::Zero();
				break;
			}
		}
		if (!m_isKnockback && isAbnormal)
			execute();
	}
		break;
	case en_Dead:
		break;
	}
	receiveDamage();
	Move();

	if (m_MPRecvTime >= m_MPrecov)
	{
		if (m_MP < m_maxMP)
		{
			m_MP += 1;
			m_MPRecvTime = 0;
		}
	}

	

	m_actionTime += IGameTime().GetFrameDeltaTime();
	m_MPRecvTime += IGameTime().GetFrameDeltaTime();
}



void Monster::execute()
{
	if (m_actions.size() == 0)
	{
		m_state = en_NowLoading;
		m_actionTime = 0;
		return;
	}
	if (m_actions[0]->Action(this))
	{
		DeleteGO(m_actions[0]);
		m_actions.erase(m_actions.begin());
	}
}

void Monster::Move()
{
	
	
	//ˆÚ“®§ŒÀ
	auto v = m_pos - CVector3::Zero();
	auto dist = v.Length();
	if (abs(dist) > m_limitDist) {
		int outSpeed = 300;
		if (m_movespeed.Length() > 0.f)
		{
			outSpeed = 0;
		}
		v.Normalize();
		v *= -1;
		v *= outSpeed;
		v += m_vKnockback;
		m_pos = m_cc.Execute(IGameTime().GetFrameDeltaTime(), v);
	}
	else
	{
		CVector3 oldPos = m_pos;
		CVector3 move = m_movespeed + m_vKnockback;
		move *= m_speed;
		m_pos = m_cc.Execute(IGameTime().GetFrameDeltaTime(), move);
	}

	m_smr->SetPosition(m_pos);
	if (m_isKnockback)
	{
		Knockback();
	}
	else
	{
		Turn();
		//TurnEx();
	}
}

void Monster::Turn()
{
	if (m_turncount > 0)
		return;
	if (m_movespeed.Length() < 0.0001f)
		return;
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	//m_turncount = 5;
	//m_rotangle = angle / m_turncount;
	m_rot.SetRotation(CVector3::AxisY(), angle);
	m_smr->SetRotation(m_rot);
}

void Monster::TurnEx()
{
	if (m_turncount <= 0)
		return;
	CQuaternion addrot = CQuaternion::Identity();
	addrot.SetRotation(CVector3::AxisY(),m_rotangle);
	m_rot.Multiply(addrot);
	m_smr->SetRotation(m_rot);
	m_turncount--;
}

void Monster::receiveDamage()
{
	bool isdam = false;
	if (m_Damage > 0)
	{
		float dm = m_Damage - m_Defense;
		if (dm <= 0)
			dm = m_Damage / m_Defense;
		if (dm > 0)
			m_HP -= dm;
		m_Damage = 0;

		isdam = true;
	}

	if (m_DamageEx)
	{
		float dm = m_DamageEx - m_ExDefense;
		if(dm <= 0)
			dm = m_DamageEx / m_ExDefense;
		if (dm > 0)
			m_HP -= dm;
		m_DamageEx = 0;

		isdam = true;
	}

	if (isdam)
	{
		Sound* se = NewGO<Sound>(0, "se");
		se->Init(L"Assets/sound/ani_fa_mon03.wav");
		se->Play();
	}
}

void Monster::StartKnockback(CVector3 v)
{
	m_vKnockback = v;
	m_vSubKnock = v / 3;
	m_isKnockback = true;
}

void Monster::SetKnockback(CVector3 v)
{
	m_vKnockback = v;
	m_vSubKnock = v;
	if (v.Length() < 1.f)
	{
		m_isKnockback = false;
	}
}

void Monster::Knockback()
{
	
	if (m_vKnockback.Length() < 0.001f)
	{
		if (m_vSubKnock.Length() < 0.05f)
		{
			m_vKnockback = CVector3::Zero();
			m_vSubKnock = CVector3::Zero();
			m_isKnockback = false;
		}
	}
	else
	{
		m_vKnockback -= m_vSubKnock;
		m_vSubKnock /= 1.5f;
	}
}

void Monster::Setpos(CVector3 v)
{
	m_pos = v;
	m_smr->SetPosition(v);
	m_cc.SetPosition(v);
}

void Monster::SetRotation(CQuaternion rot)
{
	m_rot = rot;
	m_smr->SetRotation(rot);
}

void Monster::AddAction(MonsterAction * ma)
{
	if (ma != nullptr && m_actions.size() < 3)
	{
		for (int i = 0; i < m_useActionSize; i++)
		{
			if (m_UseAction[i] == ma->GetactionID())
			{
				m_actions.push_back(ma);
				break;
			}
		}
	}
}



void Monster::anim_idle()
{
	if (en_idle > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_idle);
}

void Monster::anim_walk()
{
	if (en_walk > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_walk);
}

void Monster::anim_atack()
{
	if (en_atack > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_atack);
}


void Monster::anim_defenseF()
{
	if (en_defenseF > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_defenseF);
}

void Monster::anim_defenseM()
{
	if (en_defenseM > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_defenseM);
}

void Monster::anim_defenseE()
{
	if (en_defenseM > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_defenseE);
}

void Monster::anim_extra1()
{
	if (en_extra1 > m_AnimNum - 1)
		return;
	m_smr->PlayAnimation(en_extra1);
}

bool Monster::isAnimPlay()
{
	return m_smr->IsPlayingAnimation();
}


int Monster::GetAbnormalStateID(int num)
{
	return m_abnormalStates[num]->GetAbnormalState();
}