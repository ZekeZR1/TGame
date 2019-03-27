#pragma once

class Fade;
class MusicFade;

class ModeSelect;
class ExchangeData;
class NetPVPMode :public GameObject
{
public:
	//初期化
	NetPVPMode();

	//デストラクタ
	void OnDestroy() override;
private:


	Fade* m_fade = nullptr;				//fade
	MusicFade* m_mscfade = nullptr;		//musicfade
	ModeSelect* m_modesel = nullptr;	//modeselect
	ExchangeData* m_exdata = nullptr;	//ネットでやり取りするときに使うやつ
};