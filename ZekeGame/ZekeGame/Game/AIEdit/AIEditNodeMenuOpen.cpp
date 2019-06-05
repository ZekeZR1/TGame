#include "stdafx.h"
#include "AIEditNodeMenuOpen.h"

#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeProcess.h"
#include "../GameCursor.h"

#include "VisualAIOpen.h"

void AIEditNodeMenuOpen::OnDestroy()
{
	DeleteGO(m_back);
	for (auto sp : m_buttons)
		DeleteGO(sp);
	for (auto fr : m_fonts)
		DeleteGO(fr);
	DeleteGO(m_head);
	DeleteGO(m_close);
	DeleteGO(m_cfont);

	for (auto sp : m_marks)
		DeleteGO(sp);
}

void AIEditNodeMenuOpen::Awake()
{
	std::vector<VisualAIState> vass = VisualAIOpen::openVAs();

	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"Assets/sprite/fade_black.dds", 740, 700);

	CVector3 pos = { -357.5f,175.f,0 };
	int len = vass.size();
	int vasc = 999;
	if (vass.size() != 0)
		vasc = vass[0].num;
	for (int i = 0; i < 12; i++)
	{
		if (i == 4)
			pos = { -357.5f,-5.f,0 };
		else if (i == 8)
			pos = { -357.5f,-185.f,0 };

		SpriteRender* sp = NewGO<SpriteRender>(11, "sp");
		FontRender* fr = NewGO<FontRender>(11, "fr");
		if (vasc != 999 and i == vass[vasc].num)
		{
			//データが存在する

			SpriteRender* mark = NewGO<SpriteRender>(11, "sp");
			mark->Init(VisualAIOpen::getMark(vass[vasc].mark), 90, 90);
			CVector3 mpos = pos;
			mpos.x += 130;
			mpos.y -= 30;
			mark->SetPosition(mpos);
			m_marks.push_back(mark);

			sp->Init(L"Assets/sprite/fade_black.dds", 175, 175, true);
			//sp->SetMulCol(vass[vasc].col);
			sp->SetMulCol({ 0.7f,0.7f ,0.7f,1 });
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			wchar_t tx[3] = { '\0' };
			swprintf_s(tx, L"%d", vass[vasc].num);
			fr->Init(tx, (pos + CVector3(-20, 85.0f, 0)).ToTwo(), 0, { 1,1,1,1 }, 0.8f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fonts.push_back(fr);
			if (vasc + 1 < len)
				vasc++;
		}
		else
		{
			//データが存在しない

			sp->Init(L"Assets/sprite/fade_black.dds", 175, 175);
			sp->SetMulCol({ 0.6f,0.6f ,0.6f ,1 });
			//sp->SetPivot({ 0.5f,0.5f });
			CVector3 spos = pos;
			spos.x += 175 / 2;
			sp->SetPosition(spos);

			fr->Init(L"なし", (pos + CVector3(0, 43.75f, 0)).ToTwo(), 0, { 0.8f,0.8f,0.8f,1 }, 0.4f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fonts.push_back(fr);
		}
		pos.x += 180;

		m_buttons.push_back(sp);
	}

	m_head = NewGO<FontRender>(11, "fr");
	m_head->SetTextType(CFont::en_JapaneseBIG);
	m_head->Init(L"開くAIを選択してください", { -320,330.5f }, 0, { 1,1,1,1 }, 0.3f, { 0.5f,1.f });
	m_head->DrawShadow();

	m_close = NewGO<SpriteRender>(11, "sr");
	m_close->Init(L"Assets/sprite/fade_black.dds", 160, 64, true);
	m_close->SetPosition({ 357.5f ,-345,0 });
	m_close->SetPivot({ 1,0 });
	m_close->SetMulCol({ 0.5,0.5,0.5,1 });

	m_cfont = NewGO<FontRender>(12, "fr");
	m_cfont->Init(L"とじる", { 210.0f ,-290 }, 0, {1,1,1,1},1);
	m_cfont->SetTextType(CFont::en_Japanese);
	m_cfont->DrawShadow();
}

bool AIEditNodeMenuOpen::Start()
{
	return true;
}

void AIEditNodeMenuOpen::Update()
{
	CVector3 cpos = m_cursor->GetCursor();
	m_close->SetCollisionTarget(cpos);
	bool isLeftClick = Mouse::isTrigger(enLeftClick);
	if (m_close->isCollidingTarget())
	{
		if (isLeftClick)
		{
			PlayButtonSE();

			m_nsb->Setmenuselect(false);
			DeleteGO(this);
		}
	}

	for (int i = 0;i<12;i++)
	{
		auto sp = m_buttons[i];
		sp->SetCollisionTarget(cpos);
		if (sp->isCollidingTarget())
		{
			sp->SetScale({ 1.04,1.04,1.04 });
			if (isLeftClick)
			{
				PlayButtonSE();
				AIEditNodeProcess* proc = FindGO<AIEditNodeProcess>("process");
				proc->DeleteAll();
				char path[255];
				sprintf(path, "Assets/VisualAI/%03d.va", i);
				OpenAI(path);
				bool isfinal = false;
				for (int l = 0; l < 8; l++)
				{
					for (int o = 0; o < 3; o++)
					{
						AIEditNodeOrder* order = nullptr;
						bool isend = false;

						if (m_orders[l].one == nullptr)
						{
							break;
						}
						switch (o)
						{
						case 0:
							/*isfinal = m_orders[l].one == nullptr;
							if (isfinal)
								break;*/
							isend = m_orders[l].two == nullptr;
							order = NewGO<AIEditNodeOrder>(0, "order");
							order->makeOrder(l, 0, m_orders[l].one,isend);
							break;
						case 1:
							isend = m_orders[l].three == nullptr;
							order = NewGO<AIEditNodeOrder>(0, "order");
							order->makeOrder(l, 1, m_orders[l].two,isend);
							break;
						case 2:
							order = NewGO<AIEditNodeOrder>(0, "order");
							order->makeOrder(l, 2, m_orders[l].three,true);
							break;
						}
						if (isend or isfinal)
							break;
					}
					if (isfinal)
						break;
				}
				
				proc->Click();
				m_nsb->Setmenuselect(false);
				DeleteGO(this);
			}

		}
		else
		{
			sp->SetScale(CVector3::One());
		}
	}
}

void AIEditNodeMenuOpen::OpenAI(const char* path)
{
	FILE* f = fopen(path, "rb");

	char head[6];
	fread(head, 6, 1, f);
	int col = 0;
	fread(&col, 1, 1, f);

	for (int L = 0; L < 8; L++)
	{
		for (int D = 0; D < 3; D++)
		{
			sOrder* vso = new sOrder;
			for (int P = 0; P < 6; P++)
			{
				int R = 0;
				fread(&R, 2, 1, f);
				switch (P)
				{
				case 0:
					vso->tar = (eTarget)R;
					break;
				case 1:
					vso->nod = (eNode)R;
					break;
				case 2:
					vso->ine = (eInequ)R;
					break;
				case 3:
					vso->num = (eNum)R;
					break;
				case 4:
					vso->abn = (eAbnormal)R;
					break;
				case 5:
					vso->tec = (eTechnique)R;
					break;
				}
			}

			if (vso->tar != 0)
			{
				switch (D)
				{
				case 0:
					m_orders[L].one = vso;
					break;
				case 1:
					m_orders[L].two = vso;
					break;
				case 2:
					m_orders[L].three = vso;
					break;
				}
			}
		}
	}

	fclose(f);
}
