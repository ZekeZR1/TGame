#include "stdafx.h"
#include "NetAISelect.h"

#include "NetPVPMode.h"

#include "../GameCursor.h"
#include "../Title/MonAIPreset/MonAIPresetOpenSuper.h";
#include "../Fade/Fade.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Title/PMMonster.h"
#include "../Title/MonAIPreset/MonAIPresetSaveOpen.h"
#include "../Title/MonAIPreset/MonAIPresetLoadOpen.h"
#include "../Title/ModeSelect.h"
#include "CRatingSystem.h"
#include "RatePopup.h"

#include "../ReturnButton/ReturnButton.h"
#include "../Title/GObutton.h"
#include "../Title/MonsterSelectBack.h"
#include "../ToAiEditModeButton.h"

void NetAISelect::OnDestroy()
{
	DeleteGO(m_info);
	DeleteGO(m_back);
	DeleteGO(m_cursor);
	DeleteGO(m_msRed);
	DeleteGO(m_mlRed);
	//DeleteGO(m_GO);
	DeleteGO(m_return);
	DeleteGO(m_returnMoji);
	DeleteGO(m_status);
	for (auto i : m_pmms)
		DeleteGO(i);

	DeleteGO(m_returnButton);
	DeleteGO(m_GOb);
	DeleteGO(m_aiButton);
	DeleteGO(m_msback);
}

bool NetAISelect::Start()
{
	m_fade = FindGO<Fade>("fade");

	auto m_BGM = FindGO<Sound>("BGM");
	if (m_BGM == nullptr)
	{
		m_BGM = NewGO<Sound>(0, "BGM");
		m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_Strategy5_loop.wav", true);
		m_BGM->Play();
	}

	//m_back = NewGO<SpriteRender>(0, "sp");
	//m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);
	m_msback = NewGO<MonsterSelectBack>(0, "msb");

	m_files = PythonFileLoad::FilesLoad();

	m_cursor = NewGO<GameCursor>(0, "cursor");

	//　紅組用のチームを保存するやつ
	m_msRed = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msRed->init(this, m_cursor, L"チームを保存", { 410,130,0 }, 0);
	//　紅組用のチームを開くやつ
	m_mlRed = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlRed->init(this, m_cursor, L"チームを開く", { 410,60,0 }, 0);

	CVector3 pos = { -290,0,0 };
	for (int i = 0; i < 3; i++)
	{
		if (i == 3)
		{
			pos = { -290,-180,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i, pos);
		pmm->Setteam(i >= 3);
		pos += {260, 0, 0};
		//std::wstring ws = std::wstring(m_files[g_AIset[i]].begin(), m_files[g_AIset[i]].end());
		//std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
		//pmm->SetPython(ws.c_str(), g_AIset[i], pmm->GetAImode());
		//pmm->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
		if (g_AIset[i].AImode == 0) //AImode python
		{
			std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
			pmm->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
		}
		else //AImode visualAI
		{
			wchar_t ws[3];
			swprintf_s(ws, L"%d", g_AIset[i].AInum);
			pmm->SetPython(ws, g_AIset[i].AInum, g_AIset[i].AImode);
		}
		m_pmms.push_back(pmm);
	}

	/*m_GO = NewGO<SpriteRender>(0, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 520,240,0 });*/

	/*CVector3 repo = { -520,-260,0 };
	m_returnS.x /= 3;
	m_returnS.y /= 3;
	m_return = NewGO<SpriteRender>(0, "sp");
	m_return->Init(L"Assets/sprite/simple_button.dds", m_returnS.x, m_returnS.y);
	m_returnMoji = NewGO<SpriteRender>(0, "sp");
	m_returnMoji->Init(L"Assets/sprite/moji_return.dds", m_returnS.x, m_returnS.y, true);
	m_return->SetPosition(repo);
	m_returnMoji->SetPosition(repo);*/

	//info
	m_status = NewGO<RatingInfo>(0);
	//m_status->SetPosition(m_infoPos);
	m_status->SetPosition(m_infoPos);
	m_status->SetScale(0.5f);
	//m_info = NewGO<SpriteRender>(0);
	//m_info->Init(L"Assets/Sprite/popupback.dds", 150.f, 300.f);
	//m_info->SetPosition(m_infoPos);
	m_fade->FadeIn();

	m_returnButton = NewGO<ReturnButton>(0, "rb");
	m_returnButton->init(this, "modesel", m_cursor);

	m_GOb = NewGO<GObutton>(0, "gb");
	m_GOb->init(m_cursor, { 520,240,0 });
	
	m_aiButton = NewGO< ToAiEditModeButton>(0);
	m_aiButton->SetCurrentScene(this);
	return true;
}

void NetAISelect::Update()
{
	if (m_isfade)
	{
		if (m_fade->isFadeStop())
		{
			int moid[3];
			int aimode[3];
			for (int i = 0; i < 3; i++)
			{
				moid[i] = (MonsterID)m_pmms[i]->GetMonsterID();
				monai[i] = m_pmms[i]->GetAI();
				aimode[i] = m_pmms[i]->GetAImode();
			}
			auto n = NewGO<NetPVPMode>(0, "Game");
			n->init(m_files,monai, moid, aimode);
			//game->GamePVPmodeInit(m_files, monai,moid);
			//m_BGM->Stop();
			DeleteGO(this);
		}
		return;
	}
	if (m_aiButton->isFading())
		return;

	bool ispmm = false;
	for (auto pmm : m_pmms)
	{
		ispmm = pmm->isOpen();
		if (ispmm)
			break;
	}

	static bool isopen = false;

	//何か開いていた場合は他のものはクリックしても反応しない。
	if (!(m_msRed->IsOpen() || m_mlRed->IsOpen() || ispmm || isopen))
	{
		m_returnButton->UpdateEx<ModeSelect>();
		m_msRed->UpdateEx();
		m_mlRed->UpdateEx();
		m_aiButton->SetTarget(m_cursor->GetCursor());
		//プリセットのセーブ
		if (m_msRed->IsClick())
		{
			m_msRed->Open();
		}
		if (m_mlRed->IsClick())
		{
			m_mlRed->Open();
		}
		for (auto pmm : m_pmms)
		{
			pmm->UpdateEX();
		}


		bool ismonsel = false;
		int count = 0;
		for (auto pmm : m_pmms)
		{
			ismonsel = pmm->isMonSel();
			if (ismonsel || pmm->isSelect())
			{
				break;
			}

			count++;
		}
		if (ismonsel)
			return;
		CVector3 curs = m_cursor->GetCursor();

		//m_GO->SetCollisionTarget(curs);
		//if (m_GO->isCollidingTarget())
		//{
		//	if (Mouse::isTrigger(enLeftClick))
		//	{
		//		m_fade->FadeOut();
		//		m_isfade = true;
		//		//MusicFade* mf = NewGO<MusicFade>(0, "mf");
		//		//mf->init(m_BGM, m_vol);
		//	}
		//}

		m_GOb->UpdateEx();
		if (m_GOb->isClick())
		{
			m_fade->FadeOut();
			m_isfade = true;
			//MusicFade* mf = NewGO<MusicFade>(0, "mf");
			//mf->init(m_BGM, m_vol);
		}

		//m_returnMoji->SetCollisionTarget(curs);
		//if (m_returnMoji->isCollidingTarget())
		//{
		//	if (!isReturnOver)
		//	{
		//		m_return->Init(L"Assets/sprite/simple_button_blue.dds", m_returnS.x, m_returnS.y);
		//		isReturnOver = true;
		//	}
		//	if (Mouse::isTrigger(enLeftClick))
		//	{
		//		m_isBackFade = true;
		//		m_fade->FadeOut();
		//		//NewGO<ModeSelect>(0, "modesel");
		//		//DeleteGO(this);
		//	}
		//}
		//else if (isReturnOver)
		//{
		//	m_return->Init(L"Assets/sprite/simple_button.dds", m_returnS.x, m_returnS.y);
		//	isReturnOver = false;
		//}
	}
	isopen = ispmm;
	if (m_fade->isFadeStop() and m_isBackFade) {
		NewGO<ModeSelect>(0);
		DeleteGO(this);
	}
}
