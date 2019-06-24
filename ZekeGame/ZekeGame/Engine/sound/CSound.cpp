#include "stdafx.h"
#include "CSound.h"
#include "SoundEngine.h"

Sound::Sound() {
	
}

Sound::~Sound() {
	if (m_isInited) 
		effect->Stop();
}

bool Sound::Start() {
	return true;
}

void Sound::Update() {
	if (!m_isInited)	return;
	if (m_roofFlag)
		effect->Play(true);
	if (!isPlaying() and m_isInited) {
		//OutputDebugStringA("Delete Sound effect");
		DeleteGO(this);
	}
}

void Sound::Init(const wchar_t* filepath, bool roopflag) {
	m_roofFlag = roopflag;
	soundEffect = std::make_unique<DirectX::SoundEffect>(ISoundEngine().audEngine.get(), filepath);
	char hoge[256];
	sprintf(hoge, "filePath = %s Engine Addr = %lx\n", ISoundEngine().audEngine.get(), filepath);
	OutputDebugString(hoge);
	effect = soundEffect->CreateInstance();
	m_isInited = true;
	/*if (roopflag) {
		soundEffect = std::make_unique<DirectX::SoundEffect>(ISoundEngine().audEngine.get(), filepath);
		char hoge[256];
		sprintf(hoge, "filePath = %s Engine Addr = %lx\n", ISoundEngine().audEngine.get(), filepath);
		OutputDebugString(hoge);
		effect = soundEffect->CreateInstance();
	}
	else {
		soundEffect = std::make_unique<DirectX::SoundEffect>(ISoundEngine().audEngine.get(), filepath);
		char hoge[256];
		sprintf(hoge, "filePath = %s Engine Addr = %lx\n", ISoundEngine().audEngine.get(), filepath);
		OutputDebugString(hoge);
	}*/
}

void Sound::Play() {
	if (!m_isInited)	return;
	effect->SetVolume(volume);
	effect->SetPan(pan);
	effect->SetPitch(pitch);
	effect->Play(m_roofFlag);
}

void Sound::Stop() {
	if (!m_isInited)	return;
	effect->Stop();
	DeleteGO(this);
}

bool Sound::isPlaying() {
	if (!m_isInited)	return false;
	//return soundEffect->IsInUse();
	auto state = effect->GetState();
	return state == DirectX::SoundState::PLAYING;
}

void Sound::SetVolume(float vol) {
	if (!m_isInited)	return;
	volume = vol;
	if (m_roofFlag)
		effect->SetVolume(vol);
}