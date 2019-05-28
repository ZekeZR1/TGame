#include "stdafx.h"
#include "Book.h"

Book::Book()
{

	m_HP = 30;
	m_maxHP = 30;
	m_MP = 60;
	m_maxMP = 60;

	m_Defense = 10;
	m_ExDefense = 20;

	m_Attack = 0;
	m_ExAttack = 30;

	m_speed = 30;
	m_radius = 30;
	m_height = 70;

	m_anim[Monster::en_idle].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);

	m_anim[Monster::en_atack].Load(L"Assets/modelData/book/book_attack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);

	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(true);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(true);

	m_smr = NewGO<SkinModelRender>(0,"sr");
	m_smr->Init(L"Assets/modelData/book.cmo", m_anim, 6);
	m_AnimNum = 6;
}
