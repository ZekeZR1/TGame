#include "stdafx.h"
#include "../GameCursor.h"
#include "../../GameCamera.h"
#include "AIEditNodeButton.h"



AIEditNodeButton::~AIEditNodeButton()
{

	DeleteGO(m_spriteRender);

}

void AIEditNodeButton::Awake()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

}



bool AIEditNodeButton::Start()
{

	//仕様変更後

	for (int i = 0; i < button; i++) {
		y -= 55;
	}

	//仕様変更前
	/*for (int i = 0; i < button; i++)		//buttonがボタンの数になる
	{
		x *= -1;

		if (i % 2 == 0)
		{
			y -= 50;

		}

	}*/



	m_spriteRender = NewGO<SpriteRender>(priority, "button");
	m_spriteRender->Init(L"Assets/sprite/buttyon.dds", sizex, sizey, true);
	kari.x += x;
	kari.y += y;
	m_spriteRender->SetPosition(kari);          //仮座標

	return true;


}

//各クラスにこんな感じで書く。                //ボタンの数分ループする。
// 各クラスの.hでボタンの数を定義する。例）int button = 5;
//↓.cpp
//for (int i = 0; i < button; i++) {
//	m_aieditnodebutton = NewGO<AIEditNodeButton>(2, "button");
//	m_aieditnodebutton->SetButton(i + 1);//
//	m_aieditnodebutton->SetPos(m_position);
//	m_nodebuttons.push_back(m_aieditnodebutton);
//}


void AIEditNodeButton::Update()
{


}

