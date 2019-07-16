#include "stdafx.h"
#include "MusicFade.h"
#include "Fade.h"

void MusicFade::OnDestroy()
{
	if (m_Music != nullptr) 
		m_Music->Stop();
}

void MusicFade::init(Sound * music,float vol,float speed)
{
	m_Music = music;
	m_vol = vol;

	if (speed < 0)
	{
		m_speed = FindGO<Fade>("fade")->GetSpeed();

	}
	else
		m_speed = speed;
}

void MusicFade::Update()
{
	if (m_Music == nullptr) {
		DeleteGO(this);
		return;
	}
	else {
		m_Music->SetVolume(m_vol);
	}
	m_vol -= m_speed * IGameTime().GetFrameDeltaTime();
	if (m_vol <= 0)
	{
		m_Music->Stop();
		DeleteGO(this);
		m_vol = 0;
	}
}
