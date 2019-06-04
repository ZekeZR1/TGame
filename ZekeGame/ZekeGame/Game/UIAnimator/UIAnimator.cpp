#include "stdafx.h"
#include "UIAnimator.h"

void UIAnimator::OnDestroy()
{
	for (auto sp : m_Sprits)
		DeleteGO(sp);
	for (auto o : m_anims)
		delete o;

}

void UIAnimator::loadUI(const wchar_t* path, std::function<SpriteRender* (sUI* ui,bool &isfook)> func)
{
	FILE* file = nullptr;
	_wfopen_s(&file, path, L"rb");

	char uip[3] = { 0 };
	fread(&uip, sizeof(uip), 1, file);

	int cnt = 0;
	fread(&cnt, sizeof(int), 1, file);

	std::vector<sUI*> UIs;
	for (int i = 0; i < cnt; i++)
	{
		sUI* ui = new sUI;
		int len = 0;
		fread(&len, sizeof(int), 1, file);
		char* name = new char[len];
		fread(name, len,1, file);

		CVector2 dim = { 0,0 };
		fread(&dim, sizeof(dim), 1, file);

		CVector3 pos = { 0,0,0 };
		fread(&pos, sizeof(pos), 1, file);

		CVector3 sca = { 0,0,0 };
		fread(&sca, sizeof(sca), 1, file);

		CQuaternion rot = { 0,0,0,0 };
		fread(&rot, sizeof(rot), 1, file);

		wchar_t boneName[256];
		mbstowcs(boneName, name, 256);
		wcscpy(ui->name, boneName);
		ui->dimensions = dim;
		ui->pos = pos;
		ui->scale = sca;
		ui->rot = rot;

		UIs.push_back(ui);

		delete[] name;
	}
	fclose(file);

	for (auto UI : UIs)
	{
		bool isfook = false;
		int prio = 0;
		SpriteRender* sp = func(UI, isfook);
		if (!isfook)
		{
			std::wstring path = L"Assets/sprite/";
			path += UI->name;
			path += L".dds";
			sp->Init(path.c_str(), UI->dimensions.x, UI->dimensions.y);

			UI->pos.z = 0;
			sp->SetPosition(UI->pos);
			sp->SetScale(UI->scale);
			sp->SetRotation(UI->rot);
		}
		m_Sprits.push_back(sp);
		delete UI;
	}

}

void UIAnimator::playAnim(const wchar_t* path)
{
	for (auto an : m_anims)
	{
		delete(an);
	}
	m_anims.clear();
	m_anims.shrink_to_fit();

	FILE* file = nullptr;
	_wfopen_s(&file, path, L"rb");

	char uip[3] = { 0 };
	fread(&uip, sizeof(uip), 1, file);

	int cnt = 0;
	fread(&cnt, sizeof(int), 1, file);
	m_frameCount = cnt / m_Sprits.size();

	for (int j = 0; j < m_Sprits.size(); j++)
	{
		UIAnim* ua = new UIAnim;
		m_anims.push_back(ua);
	}

	for (int i = 0; i < cnt/ m_Sprits.size(); i++)
	{
		float time = 0;
		fread(&time, sizeof(time), 1, file);

		for (int j = 0; j < m_Sprits.size(); j++)
		{
			int num = 0;
			fread(&num, sizeof(num), 1, file);

			CVector3 pos = { 0,0,0 };
			fread(&pos, sizeof(pos), 1, file);

			CVector3 sca = { 0,0,0 };
			fread(&sca, sizeof(sca), 1, file);

			CQuaternion rot = { 0,0,0,0 };
			fread(&rot, sizeof(rot), 1, file);

			UIkeyFrame key;
			key.num = j;
			key.pos = pos;
			key.scale = sca;
			key.rot = rot;
			m_anims[j]->frames.push_back(key);
		}
	}
	m_isAnimation = true;
}

void UIAnimator::Update()
{
	if (!m_isAnimation)
		return;
	int spsize = m_Sprits.size();
	if(m_frame < m_frameCount)
	{
		m_frame += IGameTime().GetFrameDeltaTime() * m_speed;
		if (m_frame >= m_frameCount)
		{
			m_frame = 0;
			if(!m_isLoop)
				m_isAnimation = false;
			return;
		}
		for (int i = 0; i < spsize; i++)
		{
			m_Sprits[i]->SetPosition(m_anims[i]->frames[(int)m_frame].pos);
			m_Sprits[i]->SetScale(m_anims[i]->frames[(int)m_frame].scale);
			m_Sprits[i]->SetRotation(m_anims[i]->frames[(int)m_frame].rot);



		}
	}
}
