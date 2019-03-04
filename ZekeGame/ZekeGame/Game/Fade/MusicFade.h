#pragma once


class MusicFade :public GameObject
{
public:
	void OnDestroy();
	void init(Sound* music,float vol,float speed = -1);
	void Update();
private:
	Sound* m_Music = nullptr;
	float m_vol = 0;

	float m_speed = 0;
};