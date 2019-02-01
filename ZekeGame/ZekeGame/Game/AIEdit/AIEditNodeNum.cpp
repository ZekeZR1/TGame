//3
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"


AIEditNodeNum::~AIEditNodeNum()
{
	DeleteGO(m_spriteRender);
	for (SpriteRender* sp : m_spriteRenders)
	{
		DeleteGO(sp);
	}
}


bool AIEditNodeNum::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	//UI�̊��
	m_spriteRender = NewGO<SpriteRender>(5, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNode�̃{�^���̍��W���W

	int x = 35;			//�{�^����X���W
	int y = 180;		//�{�^����Y���W

						//�{�^����p
	for (int i = 0; i < button; i++)		//i�͐����񂷂����̃n�����Y i<x x�̂Ƃ��낪�{�^���̐�
	{
		x *= -1;

		if (i % 2 == 0)
		{
			y -= 50;

		}

		SetPointPos(x, y);
		sr = NewGO<SpriteRender>(6, "miniwin");
		sr->Init(L"Assets/sprite/karipoint.dds", 70, 50, true);
		sr->SetPosition(m_pointposition);
		m_spriteRenders.push_back(sr);

	}
	return true;
}


void AIEditNodeNum::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {

		m_spriteRenders[i]->SetCollisionTarget(cursorpos);

	}
	
	for (int i = 0; i < button; i++)
	{
		if (Choice3 == false) {
			if (m_spriteRenders[i]->isCollidingTarget())
			{
				Order();
			}
		}
	}

}

void AIEditNodeNum::Order()
{

	if (Mouse::isTrigger(enLeftClick)) {	//���N���b�N
		m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		//m_aieditline = NewGO<AIEditLine>(0, "Line");
		//m_aieditnodetriangle = NewGO<AIEditNodeTriangle>(0, "Triangle");
		Choice3 = true;
	}
}

//�I���{�^���̎�ł��⏕
void AIEditNodeNum::SetPointPos(int numx, int numy)
{
	//���̒l
	float x = 0;
	float y = -20;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;

}